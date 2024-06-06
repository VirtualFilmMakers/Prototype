// Fill out your copyright notice in the Description page of Project Settings.


#include "D_GameInstance.h"
#include "Runtime/NetworkReplayStreaming/NullNetworkReplayStreaming/Public/NullNetworkReplayStreaming.h"  
#include "D_SideToolWidget.h"
#include "D_CamPreviewWidget.h"
#include <Kismet/GameplayStatics.h>
#include <UMG/Public/Blueprint/WidgetBlueprintLibrary.h>
#include "D_RecorderInfoWidget.h"



UD_GameInstance::UD_GameInstance()
{
    ConstructorHelpers::FClassFinder<UD_SideToolWidget> TempWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/DKW/UI/SideTool/BP_SideToolWidget.BP_SideToolWidget_C'"));

    ConstructorHelpers::FClassFinder<UD_CamPreviewWidget> TempCamPreviewWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/DKW/UI/Camera/BP_CamPreviewWidget.BP_CamPreviewWidget_C'"));

    if (TempWidget.Succeeded()) {
        sideToolPanel = TempWidget.Class;
    }

    if (TempCamPreviewWidget.Succeeded()) {
        camPreviewWidget = TempCamPreviewWidget.Class;
    }
 
}

void UD_GameInstance::Init()
{
    Super::Init();

    //// Advanced
    // create a ReplayStreamer for FindReplays() and DeleteReplay(..)
    EnumerateStreamsPtr = FNetworkReplayStreaming::Get().GetFactory().CreateReplayStreamer();
    // Link FindReplays() delegate to function
    OnEnumerateStreamsCompleteDelegate = FOnEnumerateStreamsComplete::CreateUObject(this, &UD_GameInstance::OnEnumerateStreamsComplete);
    // Link DeleteReplay() delegate to function
    OnDeleteFinishedStreamCompleteDelegate = FOnDeleteFinishedStreamComplete::CreateUObject(this, &UD_GameInstance::OnDeleteFinishedStreamComplete);
}


#pragma region Basic Record Function

void UD_GameInstance::StartRecording(FString ReplayName, FString FriendlyName)
{
    StartRecordingReplay(ReplayName, FriendlyName);
}

void UD_GameInstance::StopRecording()
{
    StopRecordingReplay();
}

void UD_GameInstance::StartReplay(FString ReplayName)
{
    //PlayReplay(ReplayName);
    PlayReplay(ReplayName, GetWorld());
}

#pragma endregion

#pragma region Advanced Record Function

void UD_GameInstance::FindReplays()
{
    if (EnumerateStreamsPtr.Get())
    {
        TArray<FString> params;
        EnumerateStreamsPtr.Get()->EnumerateStreams(FNetworkReplayVersion(), 0, FString(), params, UpgradeEnumerateStreamsDelegate(OnEnumerateStreamsCompleteDelegate));
    }
}

void UD_GameInstance::RenameReplay(const FString& ReplayName, const FString& NewFriendlyReplayName)
{
    // Get File Info  
    FNullReplayInfo Info;

    const FString DemoPath = FPaths::Combine(*FPaths::ProjectSavedDir(), TEXT("Demos/"));
    const FString StreamDirectory = FPaths::Combine(*DemoPath, *ReplayName);
    const FString StreamFullBaseFilename = FPaths::Combine(*StreamDirectory, *ReplayName);
    const FString InfoFilename = StreamFullBaseFilename + TEXT(".replayinfo");

    TUniquePtr<FArchive> InfoFileArchive(IFileManager::Get().CreateFileReader(*InfoFilename));

    if (InfoFileArchive.IsValid() && InfoFileArchive->TotalSize() != 0)
    {
        FString JsonString;

        //InfoFileArchive << JsonString;

        Info.FromJson(JsonString);
        Info.bIsValid = true;

        InfoFileArchive->Close();
    }

    // Set FriendlyName
    Info.FriendlyName = NewFriendlyReplayName;

    // Write File Info
    TUniquePtr<FArchive> ReplayInfoFileAr(IFileManager::Get().CreateFileWriter(*InfoFilename));

    if (ReplayInfoFileAr.IsValid())
    {
        FString JsonString = Info.ToJson();
        //ReplayInfoFileAr << JsonString;

        ReplayInfoFileAr->Close();
    }
}

void UD_GameInstance::DeleteReplay(const FString& ReplayName)
{
    if (EnumerateStreamsPtr.Get())
    {
        EnumerateStreamsPtr.Get()->DeleteFinishedStream(ReplayName, UpgradeDeleteFinishedStreamDelegate(OnDeleteFinishedStreamCompleteDelegate));
    }
}



void UD_GameInstance::OnEnumerateStreamsComplete(const TArray<FNetworkReplayStreamInfo>& StreamInfos)
{
    TArray<FS_ReplayInfo> AllReplays;

    for (FNetworkReplayStreamInfo StreamInfo : StreamInfos)
    {
        if (!StreamInfo.bIsLive)
        {
            AllReplays.Add(FS_ReplayInfo(StreamInfo.Name, StreamInfo.FriendlyName, StreamInfo.Timestamp, StreamInfo.LengthInMS));
        }
    }

    OnFindReplaysComplete(AllReplays);
}


void UD_GameInstance::OnDeleteFinishedStreamComplete(const bool bDeleteSucceeded)
{
    FindReplays();
}


void UD_GameInstance::OnFindReplaysComplete(const TArray<FS_ReplayInfo>& AllReplays)
{
    // GetAll widget of class / WID Main Menu
    TArray<UUserWidget*> FoundWidgets;
    TSubclassOf<UUserWidget> WidgetClass;
    UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, FoundWidgets, WidgetClass);
   
    for (TObjectIterator<UD_RecorderInfoWidget> ObjectItr; ObjectItr; ++ObjectItr){
        UD_RecorderInfoWidget* recorderInfoWidget = *ObjectItr;
        if (recorderInfoWidget)
        {
            recorderInfoWidget->OnFindReplays(AllReplays);
        }
    }

   /* GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("1111111111111111111111"));
    for (auto Widget : FoundWidgets)
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("3333333333333333333"));
        UD_RecorderInfoWidget* recorderInfoWidget = Cast<UD_RecorderInfoWidget>(Widget);
        if (recorderInfoWidget)
        {
            
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("222222222222222222222222"));
            recorderInfoWidget->OnFindReplays(AllReplays);
        }
    }*/
}

#pragma endregion




// Panel Region
#pragma region Panel

void UD_GameInstance::OpenSideToolPanel()
{
    // if class has found from file path
    // Create Widget and add to viewport

    if (sideToolPanel)
    {
        sideToolPanelInstance = CreateWidget<UD_SideToolWidget>(GetWorld(), sideToolPanel);
        if (sideToolPanelInstance)
        {
            sideToolPanelInstance->AddToViewport();
        }
    }
}

void UD_GameInstance::CloseSideToolPanel()
{
    if (sideToolPanelInstance) {
        sideToolPanelInstance->RemoveFromParent();
    }
}

void UD_GameInstance::OpenCamPreviewWidget()
{
    if (camPreviewWidget)
    {
        camPreviewWidgetInstance = CreateWidget<UD_CamPreviewWidget>(GetWorld(), camPreviewWidget);
        if (camPreviewWidgetInstance)
        {
            camPreviewWidgetInstance->AddToViewport();
        }
    }
}

void UD_GameInstance::CloseCamPreviewWidget()
{
    if (camPreviewWidgetInstance) {
        camPreviewWidgetInstance->RemoveFromParent();
    }
}


#pragma endregion
//PossessCamera
#pragma region PossessCamera

void UD_GameInstance::UnPossessFromCamera()
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    // delete cam widget
    CloseCamPreviewWidget();
    // possess to mainPlayer
    if (mainPlayer) {
        GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, "yes");
        PlayerController->Possess(mainPlayer);
    }

}



#pragma endregion

