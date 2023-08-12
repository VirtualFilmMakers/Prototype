// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseComponent.h"
#include "PlayerFlying.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VFM_PROTO_API UPlayerFlying : public UPlayerBaseComponent
{
	GENERATED_BODY()

	UPlayerFlying();

public:

	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void SetupInputBinding(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enhanced Input")
	class UInputAction* ia_Fly;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enhanced Input")
	class UInputAction* ia_Down;

	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* bodyMesh;

	void Down(const FInputActionValue& Value);
	void Fly(const FInputActionValue& Value);
	
	
};
