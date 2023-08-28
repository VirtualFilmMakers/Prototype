// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraBaseComponent.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "O_Camera_Dron.h"
#include "O_Camera_Possess.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VFM_PROTO_API UO_Camera_Possess : public UCameraBaseComponent
{
	GENERATED_BODY()

	UO_Camera_Possess();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	// Called to bind functionality to input
	virtual void SetupInputBinding(class UInputComponent* CamInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enhanced Input")
	class UInputAction* ia_UnPosses;

	UFUNCTION(Server,Reliable)
	void DoUnposses();

	UFUNCTION(Server,Reliable)
	void ServerDoUnposses();
	UFUNCTION(NetMulticast,Reliable)
	void MulticastDoUnposses();
	
};
