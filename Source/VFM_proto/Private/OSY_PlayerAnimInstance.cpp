// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_PlayerAnimInstance.h"
#include "OSY_TESTCharacter.h"
#include "Net/UnrealNetwork.h"// 언리얼 네트워크 기능 사용을 위한 헤더



void UOSY_PlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

}

void UOSY_PlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto ownerPawn=TryGetPawnOwner();
	auto player= Cast<AOSY_TESTCharacter>(ownerPawn);

	if (player != nullptr)
	{
		// 3. forward vector 가 필요하다.
		FVector forward = player->GetActorForwardVector();
		// 4. 속도가 필요하다.
		FVector velocity = player->GetVelocity();
		// 5. 나를 소유하고 있는 TPSPlayer 의 속도와 forward 내적값을 할당하고싶다.
		speed = FVector::DotProduct(forward, velocity);

		// direction 값을 할당하고 싶다.
		FVector right = player->GetActorRightVector();
		direction = FVector::DotProduct(right, velocity);
	}
}
