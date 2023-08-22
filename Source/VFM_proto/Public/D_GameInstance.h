// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NetworkReplayStreaming.h"
#include "D_GameInstance.generated.h"


USTRUCT(BlueprintType)  
struct FS_ReplayInfo  
{  
	GENERATED_USTRUCT_BODY()  
    
	UPROPERTY(BlueprintReadOnly)  
		FString ReplayName;  
    
	UPROPERTY(BlueprintReadOnly)  
		FString FriendlyName;  
    
	UPROPERTY(BlueprintReadOnly)  
		FDateTime Timestamp;  
    
	UPROPERTY(BlueprintReadOnly)  
		int32 LengthInMS;  
    
	UPROPERTY(BlueprintReadOnly)  
		bool bIsValid;  
    
	FS_ReplayInfo(FString NewName, FString NewFriendlyName, FDateTime NewTimestamp, int32 NewLengthInMS)  
	{  
		ReplayName = NewName;  
		FriendlyName = NewFriendlyName;  
		Timestamp = NewTimestamp;  
		LengthInMS = NewLengthInMS;  
		bIsValid = true;  
	}  

	FS_ReplayInfo()  
	{  
		ReplayName = "Replay";  
		FriendlyName = "Replay";  
		Timestamp = FDateTime::MinValue();  
		LengthInMS = 0;  
		bIsValid = false;  
	}  
};

UCLASS()
class VFM_PROTO_API UD_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
protected:
	
	UD_GameInstance();
	//virtual void Init();

public:
	virtual void Init() override;

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


public:
	// Basic Replay Functions
	UFUNCTION(BlueprintCallable, Category = "Replays")
	void StartRecording(FString ReplayName, FString FriendlyName);

	UFUNCTION(BlueprintCallable, Category = "Replays")
	void StopRecording();

	UFUNCTION(BlueprintCallable, Category = "Replays")
	void StartReplay(FString ReplayName);

	
	// Advanced Functions
	UFUNCTION(BlueprintCallable, Category = "Replays")
	void FindReplays();

	/** Apply a new custom name to the replay (for UI only) */  
    UFUNCTION(BlueprintCallable, Category = "Replays")  
    void RenameReplay(const FString &ReplayName, const FString &NewFriendlyReplayName);   
  
	/** Delete a previously recorded replay */
    UFUNCTION(BlueprintCallable, Category = "Replays")
	void DeleteReplay(const FString &ReplayName);

	
private:
	// for FindReplays()   
	TSharedPtr<INetworkReplayStreamer> EnumerateStreamsPtr;
	FOnEnumerateStreamsComplete OnEnumerateStreamsCompleteDelegate;

	void OnEnumerateStreamsComplete(const TArray<FNetworkReplayStreamInfo>& StreamInfos);

	// for DeleteReplays(..)  
	FOnDeleteFinishedStreamComplete OnDeleteFinishedStreamCompleteDelegate;

	void OnDeleteFinishedStreamComplete(const bool bDeleteSucceeded);

protected:  
	//UFUNCTION(BlueprintImplementableEvent, Category = "Replays")  
	UFUNCTION(Category = "Replays")  
	void OnFindReplaysComplete(const TArray<FS_ReplayInfo> &AllReplays);
};
