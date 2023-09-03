// Fill out your copyright notice in the Description page of Project Settings.


#include "D_ParLightWidget.h"
#include <UMG/Public/Components/VerticalBox.h>

void UD_ParLightWidget::NativeConstruct()
{
	
	TArray<UWidget*> tempChildWidget = VB_Parametars->GetAllChildren();
	for (int i = 0; i < tempChildWidget.Num(); i++){
		sliderList.Add(Cast<BP_SliderModule>(tempChildWidget[i]));



	}
}
