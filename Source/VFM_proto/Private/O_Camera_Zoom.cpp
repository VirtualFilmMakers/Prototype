// Fill out your copyright notice in the Description page of Project Settings.


#include "O_Camera_Zoom.h"
#include "O_CameraBase.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Net/UnrealNetwork.h"// 언리얼 네트워크 기능 사용을 위한 헤더

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
		float NewFOV=me->CameraBase_CamComp->FieldOfView+ZoomValue*me->CameraBase_ZoomStep;
		me->CameraBase_CamComp->FieldOfView= FMath::Clamp(NewFOV,me->CameraBase_MinFOV,me->CameraBase_MaxFOV);

	}
}
