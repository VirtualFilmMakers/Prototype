// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "D_ParLightWidget.generated.h"

class UVerticalBox;

UCLASS()
class VFM_PROTO_API UD_ParLightWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UVerticalBox* VB_Parametars;

	TArray<class BP_SliderModule*> sliderList;
};
