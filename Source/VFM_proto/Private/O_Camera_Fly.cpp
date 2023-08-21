// Fill out your copyright notice in the Description page of Project Settings.


#include "O_Camera_Fly.h"
#include "O_CameraBase.h"
#include "EnhancedInputComponent.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "Net/UnrealNetwork.h"// 언리얼 네트워크 기능 사용을 위한 헤더


UO_Camera_Fly::UO_Camera_Fly()
{
	ConstructorHelpers::FObjectFinder<UInputAction> tempCameraFly(TEXT("/Script/EnhancedInput.InputAction'/Game/OSY/Inputs/IA_OSY_Fly.IA_OSY_Fly'"));
	if (tempCameraFly.Succeeded())
	{
		ia_Cam_Fly = tempCameraFly.Object;
	}
	ConstructorHelpers::FObjectFinder<UInputAction> tempCameraDown(TEXT("/Script/EnhancedInput.InputAction'/Game/OSY/Inputs/IA_OSY_Down.IA_OSY_Down'"));
	if (tempCameraDown.Succeeded())
	{
		ia_Cam_Down = tempCameraDown.Object;
	}
}

void UO_Camera_Fly::BeginPlay()
{
	Super::BeginPlay();

	me = Cast<AO_CameraBase>(GetOwner());

}
void UO_Camera_Fly::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UO_Camera_Fly::SetupInputBinding(class UInputComponent* CamInputComponent)
{

	UEnhancedInputComponent* CameraFlyInput = CastChecked<UEnhancedInputComponent>(CamInputComponent);
	if (CameraFlyInput)
	{
		
		CameraFlyInput->BindAction(ia_Cam_Fly, ETriggerEvent::Triggered, this, &UO_Camera_Fly::Cam_Fly);
		CameraFlyInput->BindAction(ia_Cam_Down, ETriggerEvent::Triggered, this, &UO_Camera_Fly::Cam_Down);
	}

}

void UO_Camera_Fly::Cam_Down(const FInputActionValue& Value)
{
	me->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	ServerCam_Down(Value);
}

void UO_Camera_Fly::ServerCam_Down_Implementation(const FInputActionValue& Value)
{
	me->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	MulticastCam_Down(Value);
}

void UO_Camera_Fly::MulticastCam_Down_Implementation(const FInputActionValue& Value)
{
	me->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void UO_Camera_Fly::Cam_Fly(const FInputActionValue& Value)
{

	me->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	float UpValue = Value.Get<float>() / 4;
	if (UpValue != 0.f)
	{
		me->AddMovementInput(me->GetActorUpVector(), UpValue, true);
	}
	ServerCam_Fly(Value);
}

void UO_Camera_Fly::ServerCam_Fly_Implementation(const FInputActionValue& Value)
{
	me->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	float UpValue = Value.Get<float>() / 4;
	if (UpValue != 0.f)
	{
		me->AddMovementInput(me->GetActorUpVector(), UpValue, true);
	}
	MulticastCam_Fly(Value);
}

void UO_Camera_Fly::MulticastCam_Fly_Implementation(const FInputActionValue& Value)
{
	me->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	float UpValue = Value.Get<float>() / 4;
	if (UpValue != 0.f)
	{
		me->AddMovementInput(me->GetActorUpVector(), UpValue, true);
	}
}

