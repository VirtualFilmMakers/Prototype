// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "D_ControllableAsset.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UD_ControllableAsset : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class VFM_PROTO_API ID_ControllableAsset
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact|FromInteract")
	void OpenAssetPanel(AActor* AssetWithControlPanel);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact|FromInteract")
	void CloseAssetPanel(AActor* AssetWithControlPanel);
};
