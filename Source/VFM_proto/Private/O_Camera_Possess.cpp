// Fill out your copyright notice in the Description page of Project Settings.


#include "O_Camera_Possess.h"
#include "O_PlayerController.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"

UO_Camera_Possess::UO_Camera_Possess()
{
	ConstructorHelpers::FObjectFinder<UInputAction> tempia_UnPosses(TEXT("/Script/EnhancedInput.InputAction'/Game/OSY/Inputs/IA_OSY_UnPossess.IA_OSY_UnPossess'"));
	if (tempia_UnPosses.Succeeded())
	{
		ia_UnPosses = tempia_UnPosses.Object;
	}
}

void UO_Camera_Possess::BeginPlay()
{
	Super::BeginPlay();
}

void UO_Camera_Possess::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

}

void UO_Camera_Possess::SetupInputBinding(class UInputComponent* CamInputComponent)
{
	UEnhancedInputComponent* DronPossessInput = CastChecked<UEnhancedInputComponent>(CamInputComponent);
	if (DronPossessInput)
	{

		DronPossessInput->BindAction(ia_UnPosses, ETriggerEvent::Triggered, this, &UO_Camera_Possess::DoUnposses);
	}
}

void UO_Camera_Possess::DoUnposses_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("pppppp"));
	AO_PlayerController* mypc = Cast<AO_PlayerController>(me->GetController());

	// 	if (mypc != nullptr && mypc->lastPlayer != nullptr)
	// 	{
	UE_LOG(LogTemp, Warning, TEXT("lastPlayer : %s"), mypc->lastPlayer != nullptr ? *mypc->lastPlayer->GetName() : *FString("Null"));
	mypc->UnPossess();
	mypc->Possess(mypc->lastPlayer);
	// 	}
	// 	
}

void UO_Camera_Possess::ServerDoUnposses_Implementation()
{

}

void UO_Camera_Possess::MulticastDoUnposses_Implementation()
{

}
