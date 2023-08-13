// Fill out your copyright notice in the Description page of Project Settings.


#include "D_LightBase.h"
#include "Blueprint/UserWidget.h"
#include <Components/SceneComponent.h>
#include "D_ControllableAsset.h"

// Sets default values
AD_LightBase::AD_LightBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    //headJoint = CreateDefaultSubobject<USceneComponent>("headJoint");
}

// Called when the game starts or when spawned
void AD_LightBase::BeginPlay()
{
	Super::BeginPlay();
	
     
}

// Called every frame
void AD_LightBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AD_LightBase::CloseAssetPanel_Implementation(AActor* AssetWithControlPanel)
{
	ID_ControllableAsset::CloseAssetPanel_Implementation(AssetWithControlPanel);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("CloseAssetPanel"));
}

void AD_LightBase::OpenAssetPanel_Implementation(AActor* AssetWithControlPanel)
{
	ID_ControllableAsset::OpenAssetPanel_Implementation(AssetWithControlPanel);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("OpenAssetPanel"));
}


