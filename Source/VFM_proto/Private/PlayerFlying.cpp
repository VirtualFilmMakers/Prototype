// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFlying.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "OSY_TESTCharacter.h"

void UPlayerFlying::BeginPlay()
{
	Super::BeginPlay();
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

	me->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	float UpValue = Value.Get<float>() / 4;
	if (UpValue != 0.f)
	{
		me->AddMovementInput(me->GetActorUpVector(), UpValue, true);
	}
}

void UPlayerFlying::Down(const FInputActionValue& Value)
{
	me->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}
