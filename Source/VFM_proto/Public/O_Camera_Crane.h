// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "O_CameraBase.h"
#include "O_Camera_Crane.generated.h"

/**
 * 
 */
UCLASS()
class VFM_PROTO_API AO_Camera_Crane : public AO_CameraBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AO_Camera_Crane();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	class UStaticMeshComponent* Crane_sub01;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	class UStaticMeshComponent* Crane_sub02;


	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Enhanced Input")
	class UInputMappingContext* CraneInputMapping;



	
};
