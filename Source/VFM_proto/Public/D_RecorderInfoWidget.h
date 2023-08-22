// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "D_RecorderInfoWidget.generated.h"

struct FS_ReplayInfo;

UCLASS(Blueprintable)
class VFM_PROTO_API UD_RecorderInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Replays")
	void OnFindReplays(const TArray<FS_ReplayInfo>& AllReplays);
};
