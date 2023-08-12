// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MHAnimInstance.generated.h"

/**
 * 
 */

 

UCLASS()
class VFM_PROTO_API UMHAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	
	
	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MHAnimSettings)
	int16 basicIdle = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MHAnimSettings)
	int16 basicWalk = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MHAnimSettings)
	bool sitOnGround = 2;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MHAnimSettings)
	bool sitOnChair = 3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MHAnimSettings)
	bool standingTalk = 4; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MHAnimSettings)
	bool standingClap = 5; */
	//
	//UPROPERTY(EditAnywhere)
	//FString CurrentState; //현재 메타휴먼의 애님 상태
	
	

public:

	
};
 