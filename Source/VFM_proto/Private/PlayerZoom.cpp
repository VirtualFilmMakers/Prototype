// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerZoom.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "OSY_TESTCharacter.h"
#include "GameFramework/SpringArmComponent.h"

void UPlayerZoom::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerZoom::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerZoom::SetupInputBinding(class UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* ZoomInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (ZoomInput)
	{
		ZoomInput->BindAction(ia_Zoom, ETriggerEvent::Triggered, this, &UPlayerZoom::Zoom);
	}

}


void UPlayerZoom::Zoom(const FInputActionValue& Value)
{
	if (me->Controller != nullptr)
	{	
		float ZoomValue = Value.Get<float>();
		float NewTargetArmLength = me->springArmComp->TargetArmLength + ZoomValue * me->ZoomStep;
		me->springArmComp->TargetArmLength = FMath::Clamp(NewTargetArmLength, me->MinZoomLength, me->MaxZoomLength);
	}

}
