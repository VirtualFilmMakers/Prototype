// Fill out your copyright notice in the Description page of Project Settings.


#include "O_Camera_Look.h"
#include "O_CameraBase.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
//#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"

UO_Camera_Look::UO_Camera_Look()
{
	ConstructorHelpers::FObjectFinder<UInputAction> tempCam_Look(TEXT("/Script/EnhancedInput.InputAction'/Game/OSY/Inputs/IA_OSY_Look.IA_OSY_Look'"));
	if (tempCam_Look.Succeeded())
	{
		ia_Cam_Look = tempCam_Look.Object;
	}
}

void UO_Camera_Look::BeginPlay()
{

	Super::BeginPlay();
}

void UO_Camera_Look::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UO_Camera_Look::SetupInputBinding(class UInputComponent* CamInputComponent)
{

	UEnhancedInputComponent* CameraLookInput = CastChecked<UEnhancedInputComponent>(CamInputComponent);
	if (CameraLookInput)
	{

		CameraLookInput->BindAction(ia_Cam_Look, ETriggerEvent::Triggered, this, &UO_Camera_Look::Cam_Look);

	}
}

void UO_Camera_Look::Cam_Look(const FInputActionValue& Value)
{

 	if (me->Controller != nullptr)
 	{
		FVector2D CameraLookValue = Value.Get<FVector2D>();
		if (CameraLookValue.X != 0.f)
		{
			me->AddControllerYawInput(CameraLookValue.X);
		}
		if (CameraLookValue.Y != 0.f)
		{
			me->  AddControllerPitchInput(CameraLookValue.Y);
		}
	}

}
