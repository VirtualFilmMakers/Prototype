// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraRender.generated.h"

UCLASS()
class VFM_PROTO_API ACameraRender : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraRender();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// RenderTarget
	//UPROPERTY(EditAnywhere)
	//UTextureRenderTarget2D* renderTex;

	//// ¿ø¼®½Ü ÄÚµå
	//UFUNCTION(BlueprintCallable)
	//void RenderFromRenderTarget(UTextureRenderTarget2D* inRenderTex);

	//
	//void SaveRenderTargetToDisk(UTextureRenderTarget2D* InRenderTarget, FString Filename);

};
