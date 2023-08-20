// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraBaseComponent.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "O_Camera_Fly.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VFM_PROTO_API UO_Camera_Fly : public UCameraBaseComponent
{
	GENERATED_BODY()

	UO_Camera_Fly();

public:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void SetupInputBinding(class UInputComponent* CamInputComponent) override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enhanced Input")
	class UInputAction* ia_Cam_Fly;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enhanced Input")
	class UInputAction* ia_Cam_Down;

	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* bodyMesh;


	void Cam_Down(const FInputActionValue& Value);
	void Cam_Fly(const FInputActionValue& Value);

	//Server
	UFUNCTION(Server,Reliable)
	void ServerCam_Down();
	UFUNCTION(NetMulticast,Reliable)
	void MulticastCam_Down();
	UFUNCTION(Server,Reliable)
	void ServerCam_Fly();
	UFUNCTION(NetMulticast,Reliable)
	void MulticastCam_Fly();
	
};
