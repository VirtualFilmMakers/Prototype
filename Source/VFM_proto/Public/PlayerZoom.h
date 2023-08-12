// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseComponent.h"
#include "PlayerZoom.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VFM_PROTO_API UPlayerZoom : public UPlayerBaseComponent
{
	GENERATED_BODY()

	UPlayerZoom();

public:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void SetupInputBinding(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enhanced Input")
	class UInputAction* ia_Zoom;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	float MinZoomLength=0.f;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	float MaxZoomLength=1000.f;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	float DefaultArmLength=600.f;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	float ZoomStep=10.f;

	void Zoom(const FInputActionValue& Value);
};
