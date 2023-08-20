// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NetworkReplayStreaming.h"
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

	UPROPERTY()
	APawn* mainPlayer;
	
	// Function
	UFUNCTION(BlueprintCallable)
	void OpenSideToolPanel();

	UFUNCTION(BlueprintCallable)
	void CloseSideToolPanel();

	UFUNCTION(BlueprintCallable)
	void OpenCamPreviewWidget(); 

	UFUNCTION(BlueprintCallable)
	void CloseCamPreviewWidget();

	UFUNCTION(BlueprintCallable)
	void SetMainActor(APawn* actor){mainPlayer = actor;}

	UFUNCTION(BlueprintCallable)
	void UnPossessFromCamera();


	// record System
	virtual void Init() override;

	UPROPERTY(EditDefaultsOnly, Category = "Replays")
	FString RecordingName;

	UPROPERTY(EditDefaultsOnly, Category = "Replays")
	FString FriendlyRecordingName;

	UFUNCTION(BlueprintCallable, Category = "Replays")
	void StartRecording();

	UFUNCTION(BlueprintCallable, Category = "Replays")
	void StopRecording();

	UFUNCTION(BlueprintCallable, Category = "Replays")
	void StartReplay();
	
};
