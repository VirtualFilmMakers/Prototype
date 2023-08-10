// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFlying.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "OSY_TESTCharacter.h"
#include "OSY_PlayerAnimInstance.h"

UPlayerFlying::UPlayerFlying()
{
	ConstructorHelpers::FObjectFinder<UInputAction> tempFly(TEXT("/Script/EnhancedInput.InputAction'/Game/OSY/Inputs/IA_OSY_Fly.IA_OSY_Fly'"));
	if (tempFly.Succeeded())
	{
		ia_Fly = tempFly.Object;
	}
	ConstructorHelpers::FObjectFinder<UInputAction> tempDown(TEXT("/Script/EnhancedInput.InputAction'/Game/OSY/Inputs/IA_OSY_Down.IA_OSY_Down'"));
	if (tempDown.Succeeded())
	{
		ia_Down = tempDown.Object;
	}
}

void UPlayerFlying::BeginPlay()
{
	Super::BeginPlay();

	me=Cast<AOSY_TESTCharacter>(GetOwner());
	if (me)
	{
		 bodyMesh = Cast<USkeletalMeshComponent>(me->GetDefaultSubobjectByName(TEXT("Body")));

	}
}

void UPlayerFlying::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerFlying::SetupInputBinding(class UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* FlyInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (FlyInput)
	{

		FlyInput->BindAction(ia_Fly, ETriggerEvent::Triggered, this, &UPlayerFlying::Fly);
		FlyInput->BindAction(ia_Down, ETriggerEvent::Triggered, this, &UPlayerFlying::Down);
	}

}
void UPlayerFlying::Fly(const FInputActionValue& Value)
{

	// me의 모드를 플라잉으로 누고 anim에 있는 bIsAir를 트루로 만든다
	me->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	if (bodyMesh == nullptr)
	{
		return;
	}
	UOSY_PlayerAnimInstance* anim = Cast<UOSY_PlayerAnimInstance>(bodyMesh->GetAnimInstance());
 	if (anim)
 	{
 		anim->bInAir= true;
 	}
	float UpValue = Value.Get<float>() / 4;
	if (UpValue != 0.f)
	{
		me->AddMovementInput(me->GetActorUpVector(), UpValue, true);
	}
}

void UPlayerFlying::Down(const FInputActionValue& Value)
{
	me->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	if (bodyMesh == nullptr)
	{
		return;
	}
	UOSY_PlayerAnimInstance* anim = Cast<UOSY_PlayerAnimInstance>(bodyMesh->GetAnimInstance());
	if (anim)
	{
		anim->bInAir = false;
	}

}
