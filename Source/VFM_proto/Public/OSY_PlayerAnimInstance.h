// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "OSY_PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class VFM_PROTO_API UOSY_PlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	// Tick 처럼 매프레임 갱신
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	//뷰 파인더인가 확인하는 불값
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MySettings)
	bool bHasViewFinder=true;

	//플레이어가 공중에 있는지 체크하는 불값
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MySettings)
	bool bInAir= false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MySettings)
	bool bIsStart= true;

	// 플레이어 이동속도
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=MySettings)
	float speed = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=MySettings)
	float direction = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=MySettings)
	float deltaRot=0;

private:

	UPROPERTY()
	class AOSY_TESTCharacter* player;

	UPROPERTY()
	class UCharacterMovementComponent* movementComp;

	float CalculateDir(FVector velocity,FRotator rot);

};
