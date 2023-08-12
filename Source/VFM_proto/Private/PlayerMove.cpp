// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMove.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "InputAction.h"

UPlayerMove::UPlayerMove()
{

	ConstructorHelpers::FObjectFinder<UInputAction> tempMove(TEXT("/Script/EnhancedInput.InputAction'/Game/OSY/Inputs/IA_OSY_Move.IA_OSY_Move'"));
	if (tempMove.Succeeded())
	{
		ia_Move=tempMove.Object;
	}
}

void UPlayerMove::BeginPlay()
{
	Super::BeginPlay();

	// 초기 속도 설정
	moveComp->MaxWalkSpeed = walkSpeed;
	returnSpeed = walkSpeed;
}

void UPlayerMove::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	moveComp->MaxWalkSpeed = FMath::Lerp(moveComp->MaxWalkSpeed, returnSpeed, 5 * DeltaTime);
}

void UPlayerMove::SetupInputBinding(class UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* MoveInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (MoveInput)
	{
		MoveInput->BindAction(ia_Move, ETriggerEvent::Triggered, this, &UPlayerMove::Move);
	}

}

void UPlayerMove::Move(const FInputActionValue& Value)
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


