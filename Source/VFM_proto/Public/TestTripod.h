// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "O_CameraBase.h"
#include "TestTripod.generated.h"

/**
 * 
 */
UCLASS()
class VFM_PROTO_API ATestTripod : public AO_CameraBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATestTripod();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 카메라를 회전을 받을 스프링암
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	class USpringArmComponent *compSpring;
	// 카메라 상단
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	class UBoxComponent* compUpBox;
	// 카메라 하단
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	class UBoxComponent* compDownBox;
};
