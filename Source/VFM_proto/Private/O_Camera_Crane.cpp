// Fill out your copyright notice in the Description page of Project Settings.


#include "O_Camera_Crane.h"
#include "O_CameraBase.h"
#include "Camera/CameraComponent.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"

AO_Camera_Crane::AO_Camera_Crane()
{
	PrimaryActorTick.bCanEverTick = true;

	//Crane_sub01--------------------------------------
	Crane_sub01 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Crane_sub01"));
	Crane_sub01->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh>tempCrane_sub01(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/Crane/Resource/Crane_sub01.Crane_sub01'"));
	if (tempCrane_sub01.Succeeded())
	{
		Crane_sub01->SetStaticMesh(tempCrane_sub01.Object);
	}

	//Crane_sub02--------------------------------------
	Crane_sub02 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Crane_sub02"));
	Crane_sub02->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh>tempCrane_sub02(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/Crane/Resource/Crane_sub02.Crane_sub02'"));
	if (tempCrane_sub02.Succeeded())
	{
		Crane_sub02->SetStaticMesh(tempCrane_sub02.Object);
	}

	

}

void AO_Camera_Crane::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(CraneInputMapping, 0);
		}
	}
}

void AO_Camera_Crane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AO_Camera_Crane::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
