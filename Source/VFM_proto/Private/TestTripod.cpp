// Fill out your copyright notice in the Description page of Project Settings.


#include "TestTripod.h"
#include "O_CameraBase.h"
#include "Camera/CameraComponent.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"


ATestTripod::ATestTripod()
{
	PrimaryActorTick.bCanEverTick = true;

	compSpring = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArm"));
	compUpBox = CreateDefaultSubobject<UBoxComponent>(TEXT("compUpBox"));

	compUpBox = CreateDefaultSubobject<UBoxComponent>(TEXT("compUpBox"));
	
}

void ATestTripod::BeginPlay()
{

}

void ATestTripod::Tick(float DeltaTime)
{

}

void ATestTripod::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{

}
