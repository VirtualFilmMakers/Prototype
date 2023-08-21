// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraBaseComponent.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "O_Camera_Tripod_UpDown.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VFM_PROTO_API UO_Camera_Tripod_UpDown : public UCameraBaseComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UO_Camera_Tripod_UpDown();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	// Called to bind functionality to input
	virtual void SetupInputBinding(class UInputComponent* CamInputComponent) override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enhanced Input")
	class UInputAction* ia_Cam_Up;

	void Cam_Up(const FInputActionValue& Value);

	UFUNCTION(Server,Reliable)
	void ServerCam_UP(const FInputActionValue& Value);
	UFUNCTION(NetMulticast,Reliable)
	void MulticastCam_UP(const FInputActionValue& Value);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enhanced Input")
	class UInputAction* ia_Cam_Turn;

	void Cam_Turn(const FInputActionValue& Value);


	float TripodUpValue;

	FVector NewTirpodLocation;


	
};
