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


	}

}

void UON_GameInstance::CreateMySession(FText roomName)
{
	FOnlineSessionSettings OSessionsettings;

	// LAN 연결인지 Dedicate 연결인지 설정한다.
	OSessionsettings.bIsDedicated= false;
	OSessionsettings.bIsLANMatch= true;

	//2. 검색가능한 방으로 설정한다.
	OSessionsettings.bShouldAdvertise= true;

	//3. 자기 정보를 전달될수 있게 설정한다.
	OSessionsettings.bUsesPresence= true;

	//4. 진행중에 난입이 가능할것인가 설정한다.
	OSessionsettings.bAllowJoinInProgress= true;
	OSessionsettings.bAllowJoinViaPresence=true;

	//5. 입장가능인원을 설정한다.
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

