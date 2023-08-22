// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerLook.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"

UPlayerLook::UPlayerLook()
{
	ConstructorHelpers::FObjectFinder<UInputAction> tempLook(TEXT("/Script/EnhancedInput.InputAction'/Game/OSY/Inputs/IA_OSY_Look.IA_OSY_Look'"));
	if (tempLook.Succeeded())
	{
		ia_Look = tempLook.Object;
	}
}

void UPlayerLook::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerLook::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerLook::SetupInputBinding(class UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* LookInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (LookInput)
	{
		LookInput->BindAction(ia_Look, ETriggerEvent::Triggered, this, &UPlayerLook::Look);
	}
}


void UPlayerLook::Look(const FInputActionValue& Value)
{
	if (me->Controller != nullptr)
	{
		FVector2D LookValue = Value.Get<FVector2D>();
		if (LookValue.X != 0.f)
		{
			me->AddControllerYawInput(LookValue.X);
		}
		if (LookValue.Y != 0.f)
		{
			me->AddControllerPitchInput(LookValue.Y);
		}
	}
}

