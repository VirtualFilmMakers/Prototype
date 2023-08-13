// Fill out your copyright notice in the Description page of Project Settings.


#include "D_GameInstance.h"
#include "D_SideToolWidget.h"
#include "D_CamPreviewWidget.h"


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
