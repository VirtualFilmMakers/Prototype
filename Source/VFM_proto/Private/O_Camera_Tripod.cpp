// Fill out your copyright notice in the Description page of Project Settings.


#include "O_Camera_Tripod.h"
#include "O_CameraBase.h"
#include "Camera/CameraComponent.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"

AO_Camera_Tripod::AO_Camera_Tripod()
{
	PrimaryActorTick.bCanEverTick = true;

	
	
	CameraBase_SpringArmComp->SetupAttachment(RootComponent);
	CameraBase_SpringArmComp->TargetArmLength=0.f;
	CameraBase_SpringArmComp->bUsePawnControlRotation=true;
	CameraBase_SpringArmComp->bEnableCameraLag= false;
	CameraBase_SpringArmComp->bEnableCameraRotationLag = false;
	CameraBase_SpringArmComp->SetRelativeLocation(FVector(-2,0,79));

	
	
	
	//compTirpodUp-----------------------
	compTirpodUp= CreateDefaultSubobject<USceneComponent>(TEXT("compTirpodUp"));
	compTirpodUp->SetupAttachment(CameraBase_SpringArmComp);
	compTirpodUp->SetRelativeLocation(FVector(0,0,-188));
	
	
	CameraBase_ACamera->SetupAttachment(compTirpodUp);
	CameraBase_ACamera->SetRelativeLocation(FVector(7,0,148));


	

	//Tripod222_Object001-----------------------------
	Tripod222_Object001 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tripod222_Object001"));
	Tripod222_Object001->SetupAttachment(compTirpodUp);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempTripod222_Object001(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/Tripod/Tripod222_Object001.Tripod222_Object001'"));
	if (tempTripod222_Object001.Succeeded())
	{
		Tripod222_Object001->SetStaticMesh(tempTripod222_Object001.Object);
	}
	
	//Tripod222_Object002-----------------------------
	Tripod222_Object002 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tripod222_Object002"));
	Tripod222_Object002->SetupAttachment(compTirpodUp);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempTripod222_Object002(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/Tripod/Tripod222_Object002.Tripod222_Object002'"));
	if (tempTripod222_Object002.Succeeded())
	{
		Tripod222_Object002->SetStaticMesh(tempTripod222_Object002.Object);
	}

	//compTirpodDown-----------------------
	compTirpodDown= CreateDefaultSubobject<USceneComponent>(TEXT("compTirpodDown"));
	compTirpodDown->SetupAttachment(RootComponent);
	compTirpodDown->SetRelativeLocation(FVector(0,0,-80));

	

	//Tripod222_Cylinder_002---------------------
	Tripod222_Cylinder_002 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tripod222_Cylinder_002"));
	Tripod222_Cylinder_002->SetupAttachment(compTirpodDown);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempTripod222_Cylinder_002(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/Tripod/Tripod222_Cylinder_002.Tripod222_Cylinder_002'"));
	if (tempTripod222_Cylinder_002.Succeeded())
	{
		Tripod222_Cylinder_002->SetStaticMesh(tempTripod222_Cylinder_002.Object);
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
