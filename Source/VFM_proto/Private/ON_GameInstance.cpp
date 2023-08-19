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
		bool Result = GetWorld()->ServerTravel("/Game/OSY/Network/ON_CreateMap?Listen",true);
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
}

void UON_GameInstance::OnFindOtherSessions(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		// 검색된 세션목록을 가져온다
		TArray<FOnlineSessionSearchResult> searchResults = sessionSearch->SearchResults;

		UE_LOG(LogTemp,Warning,TEXT("Find Sessions: %d"),searchResults.Num());

		for (FOnlineSessionSearchResult result : searchResults)
		{
			FString roomName;
			result.Session.SessionSettings.Get(FName("ROOM_NAME"),roomName);
			FString hostName;
			result.Session.SessionSettings.Get(FName("HOST_NAME"),hostName);
			int32 openNumber = result.Session.NumOpenPublicConnections;
			int32 maxNumber =  result.Session.SessionSettings.NumPublicConnections;
			int32 pingSpeed = result.PingInMs;


			UE_LOG(LogTemp,Warning,TEXT("Room Name: %s, Host Name: %s, OpenNumber: %d,MaxNumber: %d, Ping Speed: %d "),*roomName,*hostName,openNumber,maxNumber,pingSpeed);
		}
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Session search failed..."));
	}
}

