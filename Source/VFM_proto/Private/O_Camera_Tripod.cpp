// Fill out your copyright notice in the Description page of Project Settings.


#include "O_Camera_Tripod.h"
#include "O_CameraBase.h"
#include "Camera/CameraComponent.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"

AO_Camera_Tripod::AO_Camera_Tripod()
{
	PrimaryActorTick.bCanEverTick = true;



	//Tripod 세부설정
	CameraBase_SpringArmComp->bEnableCameraLag= false;
	CameraBase_SpringArmComp->bEnableCameraRotationLag = false;
	CameraBase_SpringArmComp->SetRelativeLocation(FVector(416,0,115));


	//compTirpodUp-----------------------
	compTirpodUp= CreateDefaultSubobject<USceneComponent>(TEXT("compTirpodUp"));
	compTirpodUp->SetupAttachment(RootComponent);

	//ACamera-----------------------
	ACamera= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ACamera"));
	ACamera->SetupAttachment(compTirpodUp);
	ACamera->SetRelativeLocation(FVector(0,0,105));
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempACamera(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/ACamera/ACamera.ACamera'"));
	if (tempACamera.Succeeded())
	{
		ACamera->SetStaticMesh(tempACamera.Object);
	}

	//Tripod222_Cylinder_002---------------------
	Tripod222_Cylinder_002 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tripod222_Cylinder_002"));
	Tripod222_Cylinder_002->SetupAttachment(compTirpodUp);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempTripod222_Cylinder_002(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/Tripod/Tripod222_Cylinder_002.Tripod222_Cylinder_002'"));
	if (tempTripod222_Cylinder_002.Succeeded())
	{
		Tripod222_Cylinder_002->SetStaticMesh(tempTripod222_Cylinder_002.Object);
	}


	//Tripod222_Object001-----------------------------
	Tripod222_Object001 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tripod222_Object001"));
	Tripod222_Object001->SetupAttachment(compTirpodUp);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempTripod222_Object001(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/Tripod/Tripod222_Object001.Tripod222_Object001'"));
	if (tempTripod222_Object001.Succeeded())
	{
		Tripod222_Object001->SetStaticMesh(tempTripod222_Object001.Object);
	}

		//compTirpodDown-----------------------
		compTirpodDown= CreateDefaultSubobject<USceneComponent>(TEXT("compTirpodDown"));
		compTirpodDown->SetupAttachment(RootComponent);
	
	
	//Tripod222_Object002-----------------------------
	Tripod222_Object002 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tripod222_Object002"));
	Tripod222_Object002->SetupAttachment(compTirpodDown);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempTripod222_Object002(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/Tripod/Tripod222_Object002.Tripod222_Object002'"));
	if (tempTripod222_Object002.Succeeded())
	{
		Tripod222_Object002->SetStaticMesh(tempTripod222_Object002.Object);
	}





}

void AO_Camera_Tripod::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(TripodInputMapping, 0);
		}
	}
}

void AO_Camera_Tripod::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AO_Camera_Tripod::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	
}
