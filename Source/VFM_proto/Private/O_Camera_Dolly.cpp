// Fill out your copyright notice in the Description page of Project Settings.


#include "O_Camera_Dolly.h"
#include "O_CameraBase.h"
#include "Camera/CameraComponent.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"

AO_Camera_Dolly::AO_Camera_Dolly()
{
	PrimaryActorTick.bCanEverTick = true;

	//Dolly_Object001--------------------------------------
	Dolly_Object001 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Dolly_Object001"));
	Dolly_Object001->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh>tempDolly_Object001(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/Dolly/Resource/Dolly_Object001.Dolly_Object001'"));
	if (tempDolly_Object001.Succeeded())
	{
		Dolly_Object001->SetStaticMesh(tempDolly_Object001.Object);
	}
	
	//Dolly_Object002--------------------------------------
	Dolly_Object002 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Dolly_Object002"));
	Dolly_Object002->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh>tempDolly_Object002(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/Dolly/Resource/Dolly_Object002.Dolly_Object002'"));
	if (tempDolly_Object002.Succeeded())
	{
		Dolly_Object002->SetStaticMesh(tempDolly_Object002.Object);
	}

	//Dolly_Object003--------------------------------------
	Dolly_Object003 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Dolly_Object003"));
	Dolly_Object003->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh>tempDolly_Object003(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/Dolly/Resource/Dolly_Object003.Dolly_Object003'"));
	if (tempDolly_Object003.Succeeded())
	{
		Dolly_Object003->SetStaticMesh(tempDolly_Object003.Object);
	}

	//ACamera--------------------------------------
// 	ACamera = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ACamera"));
// 	ACamera->SetupAttachment(RootComponent);
// 	ACamera->SetRelativeLocation(FVector(10,0,20));
// 	ConstructorHelpers::FObjectFinder<UStaticMesh>tempACamera(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/ACamera/ACamera.ACamera'"));
// 	if (tempACamera.Succeeded())
// 	{
// 		ACamera->SetStaticMesh(tempACamera.Object);
// 	}
}

void AO_Camera_Dolly::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DollyInputMapping, 0);
		}
	}
}

void AO_Camera_Dolly::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AO_Camera_Dolly::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
