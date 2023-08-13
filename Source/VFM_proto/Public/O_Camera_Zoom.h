// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraBaseComponent.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "O_Camera_Zoom.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VFM_PROTO_API UO_Camera_Zoom : public UCameraBaseComponent
{
	GENERATED_BODY()

	UO_Camera_Zoom();

public:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void SetupInputBinding(class UInputComponent* CamInputComponent) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enhanced Input")
	class UInputAction* ia_Cam_Zoom;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	float CamMinZoomLength=0.f;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	float CamMaxZoomLength=380.f;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	float CamDefaultArmLength=600.f;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	float CamZoomStep=10.f;

	void Cam_Zoom(const FInputActionValue& Value);
	
	
};
