// Fill out your copyright notice in the Description page of Project Settings.


#include "O_Camera_Dron_Move.h"
#include "O_CameraBase.h"
#include "EnhancedInputComponent.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Net/UnrealNetwork.h"// 언리얼 네트워크 기능 사용을 위한 헤더

UO_Camera_Dron_Move::UO_Camera_Dron_Move()
{
	ConstructorHelpers::FObjectFinder<UInputAction> tempia_Cam_DronZoom(TEXT("/Script/EnhancedInput.InputAction'/Game/OSY/Inputs/IA_OSY_Zoom.IA_OSY_Zoom'"));
	if (tempia_Cam_DronZoom.Succeeded())
	{
		ia_Cam_DronZoom = tempia_Cam_DronZoom.Object;
	}
	ConstructorHelpers::FObjectFinder<UInputAction> tempia_Cam_DronTurn(TEXT("/Script/EnhancedInput.InputAction'/Game/OSY/Inputs/IA_OSY_Look.IA_OSY_Look'"));
	if (tempia_Cam_DronTurn.Succeeded())
	{
		ia_Cam_DronTurn = tempia_Cam_DronTurn.Object;
	}
}

void UO_Camera_Dron_Move::BeginPlay()
{
	Super::BeginPlay();

	DronMe=Cast<AO_Camera_Dron>(GetOwner());
}

void UO_Camera_Dron_Move::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

}

void UO_Camera_Dron_Move::SetupInputBinding(class UInputComponent* CamInputComponent)
{
	UEnhancedInputComponent* DronInput = CastChecked<UEnhancedInputComponent>(CamInputComponent);
	if (DronInput)
	{

		DronInput->BindAction(ia_Cam_DronZoom, ETriggerEvent::Triggered, this, &UO_Camera_Dron_Move::Cam_DronZoom);
		DronInput->BindAction(ia_Cam_DronTurn, ETriggerEvent::Triggered, this, &UO_Camera_Dron_Move::Cam_DronTrun);
	}
}

void UO_Camera_Dron_Move::Cam_DronZoom(const FInputActionValue& Value)
{
	float ZoomValue = Value.Get<float>();
	float NewFOV = DronMe->compViewCam->FOVAngle + ZoomValue * me->CameraBase_ZoomStep;
	DronMe->compViewCam->FOVAngle = FMath::Clamp(NewFOV, me->CameraBase_MinFOV, me->CameraBase_MaxFOV);
}

void UO_Camera_Dron_Move::Cam_DronTrun(const FInputActionValue& Value)
{
	FVector2D DronTurnValue = Value.Get<FVector2D>();
	if (DronTurnValue.X != 0.f || DronTurnValue.Y != 0.f)
	{
		FRotator NewDronRotation = me->CameraBase_SpringArmComp->GetRelativeRotation();
		NewDronRotation.Yaw += DronTurnValue.X;
		NewDronRotation.Pitch += DronTurnValue.Y;
		me->CameraBase_SpringArmComp->SetRelativeRotation(NewDronRotation);
	}

}
