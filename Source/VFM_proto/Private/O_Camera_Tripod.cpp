// Fill out your copyright notice in the Description page of Project Settings.


#include "O_Camera_Tripod.h"
#include "O_CameraBase.h"
#include "Camera/CameraComponent.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"

AO_Camera_Tripod::AO_Camera_Tripod()
{
	PrimaryActorTick.bCanEverTick = true;

	//루트 설정
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent=RootScene;
	RootScene->SetMobility(EComponentMobility::Movable);

	CameraBase_SpringArmComp->SetupAttachment(RootComponent);
	CameraBase_SpringArmComp->TargetArmLength=0.f;
	CameraBase_SpringArmComp->bUsePawnControlRotation=true;
	CameraBase_SpringArmComp->bEnableCameraLag= false;
	CameraBase_SpringArmComp->bEnableCameraRotationLag = false;
	CameraBase_SpringArmComp->SetRelativeLocation(FVector(-2,0,79));
	CameraBase_CamComp->SetRelativeLocation(FVector(41,0,-33));
	

	//compTirpodUp-----------------------
	compTirpodUp= CreateDefaultSubobject<USceneComponent>(TEXT("compTirpodUp"));
	compTirpodUp->SetupAttachment(CameraBase_SpringArmComp);
	compTirpodUp->SetRelativeLocation(FVector(0,0,-188));
	

	//ACamera-----------------------
	ACamera= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ACamera"));
	ACamera->SetupAttachment(compTirpodUp);
	ACamera->SetRelativeLocation(FVector(5,0,148));
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempACamera(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/ACamera/ACamera.ACamera'"));
	if (tempACamera.Succeeded())
	{
		ACamera->SetStaticMesh(tempACamera.Object);
	}

	

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
	compTirpodDown->SetMobility(EComponentMobility::Static);

	

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
