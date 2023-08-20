// Fill out your copyright notice in the Description page of Project Settings.


#include "D_GameInstance.h"
#include "D_SideToolWidget.h"
#include "D_CamPreviewWidget.h"
#include <Kismet/GameplayStatics.h>


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
    RecordingName = "MyReplay";
    FriendlyRecordingName = "My Replay";
}

void UD_GameInstance::StartRecording()
{
    StartRecordingReplay(RecordingName, FriendlyRecordingName);
    UE_LOG(LogTemp, Warning, TEXT("Start Record!"));
}

void UD_GameInstance::StopRecording()
{
    StopRecordingReplay();
    UE_LOG(LogTemp, Warning, TEXT("Stop Record!"));
}

void UD_GameInstance::StartReplay()
{
    PlayReplay(RecordingName, GetWorld());
    UE_LOG(LogTemp, Warning, TEXT("Play Record!"));
}

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

