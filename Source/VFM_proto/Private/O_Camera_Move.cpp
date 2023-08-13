// Fill out your copyright notice in the Description page of Project Settings.


#include "O_Camera_Move.h"
#include "O_CameraBase.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"

UO_Camera_Move::UO_Camera_Move()
{
	ConstructorHelpers::FObjectFinder<UInputAction> tempCam_Move(TEXT("/Script/EnhancedInput.InputAction'/Game/OSY/Inputs/IA_OSY_Move.IA_OSY_Move'"));
	if (tempCam_Move.Succeeded())
	{
		ia_Cam_Move = tempCam_Move.Object;
	}
}

void UO_Camera_Move::BeginPlay()
{
	Super::BeginPlay();

	// 초기 속도 설정
	moveComp->MaxWalkSpeed = walkSpeed;
	returnSpeed = walkSpeed;
}

void UO_Camera_Move::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	moveComp->MaxWalkSpeed = FMath::Lerp(moveComp->MaxWalkSpeed, returnSpeed, 5 * DeltaTime);
}

void UO_Camera_Move::SetupInputBinding(class UInputComponent* CamInputComponent)
{
	UEnhancedInputComponent* CameraMoveInput = CastChecked<UEnhancedInputComponent>(CamInputComponent);
	if (CameraMoveInput)
	{
		CameraMoveInput->BindAction(ia_Cam_Move, ETriggerEvent::Triggered, this, &UO_Camera_Move::Cam_Move);
	}
}

void UO_Camera_Move::Cam_Move(const FInputActionValue& Value)
{
	if (me->Controller != nullptr)
	{
		FVector2D CameraMoveValue = Value.Get<FVector2D>();

		if (CameraMoveValue.X != 0.f)
		{
			me->AddMovementInput(me->GetActorRightVector(), CameraMoveValue.X);

		}
		if (CameraMoveValue.Y != 0.f)
		{
			me->AddMovementInput(me->GetActorForwardVector(), CameraMoveValue.Y);
		}

	}
}
