// Fill out your copyright notice in the Description page of Project Settings.


#include "O_Camera_Tripod_UpDown.h"
#include "O_CameraBase.h"
#include "EnhancedInputComponent.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "O_Camera_Tripod.h"
#include "Net/UnrealNetwork.h"// 언리얼 네트워크 기능 사용을 위한 헤더

UO_Camera_Tripod_UpDown::UO_Camera_Tripod_UpDown()
{

	ConstructorHelpers::FObjectFinder<UInputAction> tempCameraUp(TEXT("/Script/EnhancedInput.InputAction'/Game/OSY/Inputs/IA_OSY_Fly.IA_OSY_Fly'"));
	if (tempCameraUp.Succeeded())
	{
		ia_Cam_Up = tempCameraUp.Object;
	}
	ConstructorHelpers::FObjectFinder<UInputAction> tempCam_Turn(TEXT("/Script/EnhancedInput.InputAction'/Game/OSY/Inputs/IA_OSY_Look.IA_OSY_Look'"));
	if (tempCam_Turn.Succeeded())
	{
		ia_Cam_Turn = tempCam_Turn.Object;
	}
}

void UO_Camera_Tripod_UpDown::BeginPlay()
{
	Super::BeginPlay();
}


void UO_Camera_Tripod_UpDown::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

}

void UO_Camera_Tripod_UpDown::SetupInputBinding(class UInputComponent* CamInputComponent)
{
	UEnhancedInputComponent* CameraUpInput = CastChecked<UEnhancedInputComponent>(CamInputComponent);
	if (CameraUpInput)
	{

		CameraUpInput->BindAction(ia_Cam_Up, ETriggerEvent::Triggered, this, &UO_Camera_Tripod_UpDown::Cam_Up);
		CameraUpInput->BindAction(ia_Cam_Turn, ETriggerEvent::Triggered, this, &UO_Camera_Tripod_UpDown::Cam_Turn);
	}
}

void UO_Camera_Tripod_UpDown::Cam_Up(const FInputActionValue& Value)
{
	ServerCam_UP(Value);
}

void UO_Camera_Tripod_UpDown::ServerCam_UP_Implementation(const FInputActionValue& Value)
{
	MulticastCam_UP(Value);
}

void UO_Camera_Tripod_UpDown::MulticastCam_UP_Implementation(const FInputActionValue& Value)
{
	float TripodUpValue = Value.Get<float>() / 2;
	if (TripodUpValue != 0.f)
	{
		FVector NewTirpodLocation = me->CameraBase_SpringArmComp->GetRelativeLocation();
		NewTirpodLocation.Z += TripodUpValue;

		const float MinCameraHeight = 79.f;
		const float MaxCameraHeight = 141.f;
		NewTirpodLocation.Z = FMath::Clamp(NewTirpodLocation.Z, MinCameraHeight, MaxCameraHeight);

		me->CameraBase_SpringArmComp->SetRelativeLocation(NewTirpodLocation);
	}
}

void UO_Camera_Tripod_UpDown::Cam_Turn(const FInputActionValue& Value)
{
	FVector2D TripodTurnValue= Value.Get<FVector2D>();
	if (TripodTurnValue.X != 0.f || TripodTurnValue.Y != 0.f)
	{
		FRotator NewTripodRotation= me->CameraBase_ACamera->GetRelativeRotation();
		NewTripodRotation.Yaw +=TripodTurnValue.X;
		NewTripodRotation.Pitch +=TripodTurnValue.Y;
		me->CameraBase_ACamera->SetRelativeRotation(NewTripodRotation);
	}
}
