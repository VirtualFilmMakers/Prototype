// Fill out your copyright notice in the Description page of Project Settings.


#include "ON_GameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

UON_GameInstance::UON_GameInstance()
{
	mySessionName=TEXT("Seyoung");
}

void UON_GameInstance::Init()
{
	Super::Init();

	
	if (IOnlineSubsystem* subsys = IOnlineSubsystem::Get())
	{
		//Online Session Interface API 접근용 인스턴스 가져오기
		sessionInterface = subsys->GetSessionInterface();

		// 세션 이벤트에 함수 바인딩하기
		sessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this,&UON_GameInstance::OnCreatedMySession);


		sessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this,&UON_GameInstance::OnFindOtherSessions);

		sessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this,&UON_GameInstance::OnJoinSelectedSession);

	}

}

void UON_GameInstance::CreateMySession(FText roomName)
{
	FOnlineSessionSettings Sessionsettings;

	// LAN 연결인지 Dedicate 연결인지 설정한다.
	Sessionsettings.bIsDedicated= false;
	Sessionsettings.bIsLANMatch= IOnlineSubsystem::Get()->GetSubsystemName()== FName("NULL");

	//2. 검색가능한 방으로 설정한다.
	Sessionsettings.bShouldAdvertise= true;

	//3. 자기 정보를 전달될수 있게 설정한다.
	Sessionsettings.bUsesPresence= true;

	//4. 진행중에 난입이 가능할것인가 설정한다.
	Sessionsettings.bAllowJoinInProgress= true;
	Sessionsettings.bAllowJoinViaPresence=true;

	//5. 입장가능인원을 설정한다.
	Sessionsettings.NumPublicConnections= 6;

	//6. 세션의 추가설정을 한다.
	Sessionsettings.Set(FName("ROOM_NAME"),roomName.ToString(),EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	Sessionsettings.Set(FName("HOST_NAME"),mySessionName,EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);


	bool isSucces = sessionInterface->CreateSession(0,FName(roomName.ToString()), Sessionsettings);
	UE_LOG(LogTemp,Warning,TEXT("Result:%s"),isSucces? *FString("Success"): *FString("Failed"));
}

void UON_GameInstance::OnCreatedMySession(FName sessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		bool Result = GetWorld()->ServerTravel("/Game/QA_Map/Alpa_Main?Listen",true);
		UE_LOG(LogTemp, Warning, TEXT("Travel Result:%s"), Result ? *FString("Success") : *FString("Failed"));
	}
}

void UON_GameInstance::FindOtherSession()
{
	sessionSearch= MakeShareable(new FOnlineSessionSearch());

	// 1. 세션 검색을 LAN으로 할것인지 설정한다
	sessionSearch->bIsLanQuery= IOnlineSubsystem::Get()->GetSubsystemName() == FName("NULL");

	//2. 세션 쿼리 설정
	sessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

	//3. 세션의 검색량을 설정한다.
	sessionSearch->MaxSearchResults = 10;
	 
	sessionInterface->FindSessions(0,sessionSearch.ToSharedRef());

	onFindButtonActivation.Broadcast(false);
}

void UON_GameInstance::OnFindOtherSessions(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		// 검색된 세션목록을 가져온다
		TArray<FOnlineSessionSearchResult> searchResults = sessionSearch->SearchResults;

		UE_LOG(LogTemp,Warning,TEXT("Find Sessions: %d"),searchResults.Num());

		for (int32 i=0; i<searchResults.Num();i++)
		{
			FString roomName;
			searchResults[i].Session.SessionSettings.Get(FName("ROOM_NAME"),roomName);
			FString hostName;
			searchResults[i].Session.SessionSettings.Get(FName("HOST_NAME"),hostName);
			int32 openNumber = searchResults[i].Session.NumOpenPublicConnections;
			int32 maxNumber = searchResults[i].Session.SessionSettings.NumPublicConnections;
			int32 pingSpeed = searchResults[i].PingInMs;


			UE_LOG(LogTemp,Warning,TEXT("Room Name: %s, Host Name: %s, OpenNumber: %d,MaxNumber: %d, Ping Speed: %d "),*roomName,*hostName,openNumber,maxNumber,pingSpeed);

			// 구조체 변수에 찾은 세션 정보를 입력한다
			FSessionSlotInfo slotInfo;
			slotInfo.Set(roomName,hostName,FString::Printf(TEXT("(%d/%d)"),maxNumber-openNumber,maxNumber),pingSpeed,i);

			// 세션 정보를 델리게이트로 전파한다
			onSearchCompleted.Broadcast(slotInfo);
		}
		onFindButtonActivation.Broadcast(true);

	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Session search failed..."));
	}
}

void UON_GameInstance::JoinSelectedSession(int32 index)
{
	sessionInterface->JoinSession(0,FName(mySessionName),sessionSearch->SearchResults[index]);
}

void UON_GameInstance::OnJoinSelectedSession(FName sessionName, EOnJoinSessionCompleteResult::Type result)
{
	//UE_LOG(LogTemp,Warning,TEXT("%s"), result == EOnJoinSessionCompleteResult::Success ? *FString::Printf(TEXT("Success:%s"), *sessionName.ToString()) : *FString(TEXT("Failed")));


	switch (result)
	{
	case EOnJoinSessionCompleteResult::Success:
	{

		UE_LOG(LogTemp, Warning,TEXT("Success:%s"), *sessionName.ToString());

		APlayerController* playercon = GetWorld()->GetFirstPlayerController();

		if (playercon != nullptr)
		{
			//join된 세션 호스트의 ServerTravel 된 맵주소를 받아온다
			FString url;
			sessionInterface->GetResolvedConnectString(sessionName, url);

			// 주소를 받았다면, 그 주소를 따라서 맵 이동한다.
			if(!url.IsEmpty())
			{
				playercon->ClientTravel(url,ETravelType::TRAVEL_Absolute);
			}
		}
	}
		break;
	case EOnJoinSessionCompleteResult::SessionIsFull:
		UE_LOG(LogTemp, Warning, TEXT("SessionIsFull"));
		break;
	case EOnJoinSessionCompleteResult::SessionDoesNotExist:
		UE_LOG(LogTemp, Warning, TEXT("SessionDoesNotExist"));
		break;
	case EOnJoinSessionCompleteResult::CouldNotRetrieveAddress:
		UE_LOG(LogTemp, Warning, TEXT("CouldNotRetrieveAddress"));
		break;
	case EOnJoinSessionCompleteResult::AlreadyInSession:
		UE_LOG(LogTemp, Warning, TEXT("AlreadyInSession"));
		break;
	case EOnJoinSessionCompleteResult::UnknownError:
		UE_LOG(LogTemp, Warning, TEXT("UnknownError"));
		break;
	default:
		break;
	}
}

