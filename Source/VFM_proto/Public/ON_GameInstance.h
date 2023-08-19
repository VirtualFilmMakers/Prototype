// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "ON_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class VFM_PROTO_API UON_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	


public:
	UON_GameInstance();

	virtual void Init()override;

	UPROPERTY()
	FString mySessionName;

	IOnlineSessionPtr sessionInterface;
	TSharedPtr<FOnlineSessionSearch> sessionSearch;

	void CreateMySession(FText roomName);
	void OnCreatedMySession(FName sessionName,bool bWasSuccessful);
	void FindOtherSession();
	void OnFindOtherSessions(bool bWasSuccessful);
	
};
