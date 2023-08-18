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


	}

}

void UON_GameInstance::CreateMySession(FText roomName)
{
	FOnlineSessionSettings OSessionsettings;

	// LAN �������� Dedicate �������� �����Ѵ�.
	OSessionsettings.bIsDedicated= false;
	OSessionsettings.bIsLANMatch= true;

	//2. �˻������� ������ �����Ѵ�.
	OSessionsettings.bShouldAdvertise= true;

	//3. �ڱ� ������ ���޵ɼ� �ְ� �����Ѵ�.
	OSessionsettings.bUsesPresence= true;

	//4. �����߿� ������ �����Ұ��ΰ� �����Ѵ�.
	OSessionsettings.bAllowJoinInProgress= true;
	OSessionsettings.bAllowJoinViaPresence=true;

	//5. ���尡���ο��� �����Ѵ�.
	OSessionsettings.NumPublicConnections= 6;


	bool isSucces = sessionInterface->CreateSession(0,FName(roomName.ToString()), OSessionsettings);
	UE_LOG(LogTemp,Warning,TEXT("Result:%s"),isSucces? *FString("Success"): *FString("Failed"));
}

void UON_GameInstance::OnCreatedMySession(FName sessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		bool Result = GetWorld()->ServerTravel("/Game/OSY/Net/ON_CreateMap?Listen",true);
		UE_LOG(LogTemp, Warning, TEXT("Travel Result:%s"), Result ? *FString("Success") : *FString("Failed"));
	}
}

