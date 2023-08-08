// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveComponent.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"

void UMoveComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UMoveComponent::SetupInputBinding(class UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* MoveInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (MoveInput)
	{
		MoveInput->BindAction(ia_Move, ETriggerEvent::Triggered, this, &UMoveComponent::Move);
	}

}

void UMoveComponent::Move(const FInputActionValue& Value)
{
	// 만약 컨트롤러가 정상적으로 있다면
	if (me->Controller != nullptr)
	{
		FVector2D MoveValue = Value.Get<FVector2D>();

		if (MoveValue.X != 0.f)
		{
			me->AddMovementInput(me->GetActorRightVector(), MoveValue.X);

		}
		if (MoveValue.Y != 0.f)
		{
			me->AddMovementInput(me->GetActorForwardVector(), MoveValue.Y);
		}

	}
}
