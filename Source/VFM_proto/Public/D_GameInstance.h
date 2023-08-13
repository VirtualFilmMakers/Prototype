// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "D_GameInstance.generated.h"

/**
 * 
 */

UCLASS()
class VFM_PROTO_API UD_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
protected:
	
	UD_GameInstance();
public:
	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<class UD_SideToolWidget> sideToolPanel;
	
	/*UPROPERTY(BlueprintReadWrite)
	class UD_SideToolWidget* sideToolPanel;*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float num;

	
	// Function
	UFUNCTION(BlueprintCallable)
	void OpenSideToolPanel();

	UFUNCTION(BlueprintCallable)
	void CloseSideToolPanel();


	
};
