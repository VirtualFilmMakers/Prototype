// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "O_CameraBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FCameraInputBindingDelegate, class UInputComponent*);


UCLASS()
class VFM_PROTO_API AO_CameraBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AO_CameraBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FCameraInputBindingDelegate onCameraInputBindingDelegate;

	// 기본 스프링암
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* CameraBase_SpringArmComp;

	// 기본 카메라
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UCameraComponent* CameraBase_CamComp;

	


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraBase_MinZoomLength = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraBase_MaxZoomLength = 1000.f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraBase_DefaultArmLength = 600.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraBase_ZoomStep = 10.f;



};
