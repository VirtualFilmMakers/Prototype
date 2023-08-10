// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "D_CameraBase.generated.h"

UCLASS()
class VFM_PROTO_API AD_CameraBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AD_CameraBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void PossessToCamera();
};
