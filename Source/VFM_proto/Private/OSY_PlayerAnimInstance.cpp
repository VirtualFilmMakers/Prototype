// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_PlayerAnimInstance.h"
#include "OSY_TESTCharacter.h"
#include "Net/UnrealNetwork.h"// 언리얼 네트워크 기능 사용을 위한 헤더
#include "GameFramework/CharacterMovementComponent.h"



void UOSY_PlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	player= Cast<AOSY_TESTCharacter>(GetOwningActor());
	if (player != nullptr)
	{

		movementComp= player->GetCharacterMovement();
	}
}

void UOSY_PlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (movementComp != nullptr)
	{
		speed = movementComp->Velocity.Size2D();
		direction = CalculateDir(movementComp->Velocity,player->GetActorRotation());

		FRotator delta = (player->GetActorRotation()-player->GetBaseAimRotation()).GetNormalized();
		deltaRot= delta.Pitch;
	}

}

float UOSY_PlayerAnimInstance::CalculateDir(FVector velocity, FRotator rot)
{
	if (velocity.IsNearlyZero())
	{
		return 0.0f;
	}

	FVector forwardVector = FRotationMatrix(rot).GetUnitAxis(EAxis::X);
	FVector rightVector = FRotationMatrix(rot).GetUnitAxis(EAxis::Y);
	FVector speedVector=velocity.GetSafeNormal2D();

	float angle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(forwardVector,speedVector)));
	float rightDot = FVector::DotProduct(rightVector,speedVector);
	if (rightDot < 0)
	{
		angle*=-1.0f;
	}

	return angle;
}

void UOSY_PlayerAnimInstance::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UOSY_PlayerAnimInstance, bHasViewFinder);

}
