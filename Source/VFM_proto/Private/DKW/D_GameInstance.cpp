// Fill out your copyright notice in the Description page of Project Settings.


#include "D_GameInstance.h"
#include "D_SideToolWidget.h"


UD_GameInstance::UD_GameInstance()
{
    ConstructorHelpers::FClassFinder<UD_SideToolWidget> TempWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/DKW/UI/SideTool/BP_SideToolWidget.BP_SideToolWidget_C'"));

    if (TempWidget.Succeeded()) {
        sideToolPanel = TempWidget.Class;
    }
}

void UD_GameInstance::OpenSideToolPanel()
{
    // if there is already side Tool widget
    // return
    if (sideToolPanelInstance) return;
    
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
