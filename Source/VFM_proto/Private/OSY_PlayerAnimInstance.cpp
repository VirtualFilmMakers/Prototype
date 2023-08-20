// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_PlayerAnimInstance.h"
#include "OSY_TESTCharacter.h"
#include "Net/UnrealNetwork.h"// �𸮾� ��Ʈ��ũ ��� ����� ���� ���



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
		// 3. forward vector �� �ʿ��ϴ�.
		FVector forward = player->GetActorForwardVector();
		// 4. �ӵ��� �ʿ��ϴ�.
		FVector velocity = player->GetVelocity();
		// 5. ���� �����ϰ� �ִ� TPSPlayer �� �ӵ��� forward �������� �Ҵ��ϰ�ʹ�.
		speed = FVector::DotProduct(forward, velocity);

		// direction ���� �Ҵ��ϰ� �ʹ�.
		FVector right = player->GetActorRightVector();
		direction = FVector::DotProduct(right, velocity);
	}
}
