// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseComponent.h"
#include "PlayerMove.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VFM_PROTO_API UPlayerMove : public UPlayerBaseComponent
{
	GENERATED_BODY()

	UPlayerMove();

public:

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void SetupInputBinding(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Enhanced Input")
	class UInputAction* ia_Move;	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings")
	float walkSpeed = 600;

	// 다시 바뀔속도
	float returnSpeed = 0;
	
};
