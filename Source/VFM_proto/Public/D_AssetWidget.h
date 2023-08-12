// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "D_AssetWidget.generated.h"

/**
 * 
 */
UCLASS()
class VFM_PROTO_API UD_AssetWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Category = AssetDataSets, EditAnywhere, BlueprintReadWrite)
	TMap<FString, TSubclassOf<AActor>> actorDataMap;

	UPROPERTY(Category = AssetDataSets, EditAnywhere, BlueprintReadWrite)
	TMap<FString, TSubclassOf<AActor>> buildingDataMap;

	UPROPERTY(Category = AssetDataSets, EditAnywhere, BlueprintReadWrite)
	TMap<FString, TSubclassOf<AActor>> propsDataMap;

	UPROPERTY(Category = AssetDataSets, EditAnywhere, BlueprintReadWrite)
	TMap<FString, TSubclassOf<class AD_CameraBase>> cameraDataMap;

	UPROPERTY(Category = AssetDataSets, EditAnywhere, BlueprintReadWrite)
	TMap<FString, TSubclassOf<class AD_LightBase>> lightDataMap;


};
