// Fill out your copyright notice in the Description page of Project Settings.


#include "O_Camera_Zoom.h"
#include "O_CameraBase.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"

UO_Camera_Zoom::UO_Camera_Zoom()
{
	ConstructorHelpers::FObjectFinder<UInputAction> tempCam_Zoom(TEXT("/Script/EnhancedInput.InputAction'/Game/OSY/Inputs/IA_OSY_Zoom.IA_OSY_Zoom'"));
	if (tempCam_Zoom.Succeeded())
	{
		ia_Cam_Zoom = tempCam_Zoom.Object;
	}
}

void UO_Camera_Zoom::BeginPlay()
{
	Super::BeginPlay();
}

void UO_Camera_Zoom::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UO_Camera_Zoom::SetupInputBinding(class UInputComponent* CamInputComponent)
{
	UEnhancedInputComponent* CameraZoomInput = CastChecked<UEnhancedInputComponent>(CamInputComponent);
	if (CameraZoomInput)
	{
		CameraZoomInput->BindAction(ia_Cam_Zoom, ETriggerEvent::Triggered, this, &UO_Camera_Zoom::Cam_Zoom);
	}
}

void UO_Camera_Zoom::Cam_Zoom(const FInputActionValue& Value)
{
	if (me->Controller != nullptr)
	{
		float ZoomValue = Value.Get<float>();
		float NewTargetArmLength = me->CameraBase_SpringArmComp->TargetArmLength + ZoomValue * me->CameraBase_ZoomStep;
		me->CameraBase_SpringArmComp->TargetArmLength = FMath::Clamp(NewTargetArmLength, me->CameraBase_MinZoomLength, me->CameraBase_MaxZoomLength);
	}
}
