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
		//Online Session Interface API ���ٿ� �ν��Ͻ� ��������
		sessionInterface = subsys->GetSessionInterface();

		// ���� �̺�Ʈ�� �Լ� ���ε��ϱ�
		sessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this,&UON_GameInstance::OnCreatedMySession);


		sessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this,&UON_GameInstance::OnFindOtherSessions);

	}

}

void UON_GameInstance::CreateMySession(FText roomName)
{
	FOnlineSessionSettings Sessionsettings;

	// LAN �������� Dedicate �������� �����Ѵ�.
	Sessionsettings.bIsDedicated= false;
	Sessionsettings.bIsLANMatch= IOnlineSubsystem::Get()->GetSubsystemName()== FName("NULL");

	//2. �˻������� ������ �����Ѵ�.
	Sessionsettings.bShouldAdvertise= true;

	//3. �ڱ� ������ ���޵ɼ� �ְ� �����Ѵ�.
	Sessionsettings.bUsesPresence= true;

	//4. �����߿� ������ �����Ұ��ΰ� �����Ѵ�.
	Sessionsettings.bAllowJoinInProgress= true;
	Sessionsettings.bAllowJoinViaPresence=true;

	//5. ���尡���ο��� �����Ѵ�.
	Sessionsettings.NumPublicConnections= 6;

	//6. ������ �߰������� �Ѵ�.
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

	// 1. ���� �˻��� LAN���� �Ұ����� �����Ѵ�
	sessionSearch->bIsLanQuery= IOnlineSubsystem::Get()->GetSubsystemName() == FName("NULL");

	//2. ���� ���� ����
	sessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

	//3. ������ �˻����� �����Ѵ�.
	sessionSearch->MaxSearchResults = 10;
	 
	
	sessionInterface->FindSessions(0,sessionSearch.ToSharedRef());
}

void UON_GameInstance::OnFindOtherSessions(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		// �˻��� ���Ǹ���� �����´�
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

