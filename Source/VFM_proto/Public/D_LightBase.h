// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "D_ControllableAsset.h"
#include "D_LightBase.generated.h"

UCLASS()
class VFM_PROTO_API AD_LightBase : public AActor, public ID_ControllableAsset
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AD_LightBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = MySetting)
	TSubclassOf<UUserWidget> LightWidgetSource;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = MySetting)
	class ULightComponent* lightSource;

	UPROPERTY(BlueprintReadWrite, Category = MySetting)
    class UUserWidget* WidgetInstance;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MySetting)
	//class USceneComponent* headJoint;

	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact|FromInteract")
	virtual void OpenAssetPanel_Implementation(AActor* AssetWithControlPanel) override;

	virtual void CloseAssetPanel_Implementation(AActor* AssetWithControlPanel) override;

	//UFUNCTION(BlueprintNativeEvent)
	//void OpenPanel();
	//UFUNCTION(BlueprintNativeEvent)
	//void ClosePanel();
};
