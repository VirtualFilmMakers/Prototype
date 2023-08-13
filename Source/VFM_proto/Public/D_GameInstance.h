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

	// widget source
	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<class UD_SideToolWidget> sideToolPanel;

	UPROPERTY()
	UD_SideToolWidget* sideToolPanelInstance;

	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<class UD_CamPreviewWidget> camPreviewWidget;

	UPROPERTY()
	UD_CamPreviewWidget* camPreviewWidgetInstance;


	
	// Function
	UFUNCTION(BlueprintCallable)
	void OpenSideToolPanel();

	UFUNCTION(BlueprintCallable)
	void CloseSideToolPanel();

	UFUNCTION(BlueprintCallable)
	void OpenCamPreviewWidget(); 

	UFUNCTION(BlueprintCallable)
	void CloseCamPreviewWidget();




	
};
