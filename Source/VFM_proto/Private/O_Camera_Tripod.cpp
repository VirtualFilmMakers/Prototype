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
	//Tripod2_Cylinder_002-----------------------
	Tripod2_Cylinder_002= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tripod2_Cylinder_002"));
	Tripod2_Cylinder_002->SetupAttachment(compTirpodUp);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempTripod2_Cylinder_002(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/Tripod/Resource/Tripod2_Cylinder_002.Tripod2_Cylinder_002'"));
	if (tempTripod2_Cylinder_002.Succeeded())
	{
		Tripod2_Cylinder_002->SetStaticMesh(tempTripod2_Cylinder_002.Object);
	}

	//Tripod2_Cylinder_004-----------------------
	Tripod2_Cylinder_004= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tripod2_Cylinder_004"));
	Tripod2_Cylinder_004->SetupAttachment(compTirpodUp);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempTripod2_Cylinder_004(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/Tripod/Resource/Tripod2_Cylinder_004.Tripod2_Cylinder_004'"));
	if (tempTripod2_Cylinder_004.Succeeded())
	{
		Tripod2_Cylinder_004->SetStaticMesh(tempTripod2_Cylinder_004.Object);
	}

	//Tripod2_Cylinder_005-----------------------
	Tripod2_Cylinder_005= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tripod2_Cylinder_005"));
	Tripod2_Cylinder_005->SetupAttachment(compTirpodUp);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempTripod2_Cylinder_005(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/Tripod/Resource/Tripod2_Cylinder_005.Tripod2_Cylinder_005'"));
	if (tempTripod2_Cylinder_005.Succeeded())
	{
		Tripod2_Cylinder_005->SetStaticMesh(tempTripod2_Cylinder_005.Object);
	}

	//Tripod2_Cylinder_006-----------------------
	Tripod2_Cylinder_006= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tripod2_Cylinder_006"));
	Tripod2_Cylinder_006->SetupAttachment(compTirpodUp);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempTripod2_Cylinder_006(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/Tripod/Resource/Tripod2_Cylinder_006.Tripod2_Cylinder_006'"));
	if (tempTripod2_Cylinder_006.Succeeded())
	{
		Tripod2_Cylinder_006->SetStaticMesh(tempTripod2_Cylinder_006.Object);
	}

	//Tripod2_Cylinder_008-----------------------
	Tripod2_Cylinder_008= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tripod2_Cylinder_008"));
	Tripod2_Cylinder_008->SetupAttachment(compTirpodUp);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempTripod2_Cylinder_008(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/Tripod/Resource/Tripod2_Cylinder_008.Tripod2_Cylinder_008'"));
	if (tempTripod2_Cylinder_008.Succeeded())
	{
		Tripod2_Cylinder_008->SetStaticMesh(tempTripod2_Cylinder_008.Object);
	}

	//Tripod2_Gewinde-----------------------
	Tripod2_Gewinde = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tripod2_Gewinde"));
	Tripod2_Gewinde->SetupAttachment(compTirpodUp);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempTripod2_Gewinde(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/Tripod/Resource/Tripod2_Gewinde.Tripod2_Gewinde'"));
	if (tempTripod2_Gewinde.Succeeded())
	{
		Tripod2_Gewinde->SetStaticMesh(tempTripod2_Gewinde.Object);
	}

	//compTirpodDown-----------------------
	compTirpodDown= CreateDefaultSubobject<USceneComponent>(TEXT("compTirpodDown"));
	compTirpodDown->SetupAttachment(RootComponent);

	//Tripod2_Cylinder-----------------------
	Tripod2_Cylinder = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tripod2_Cylinder"));
	Tripod2_Cylinder->SetupAttachment(compTirpodDown);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempTripod2_Cylinder(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/Tripod/Resource/Tripod2_Cylinder.Tripod2_Cylinder'"));
	if (tempTripod2_Cylinder.Succeeded())
	{
		Tripod2_Cylinder->SetStaticMesh(tempTripod2_Cylinder.Object);
	}

	//Tripod2_Cylinder_001-----------------------
	Tripod2_Cylinder_001 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tripod2_Cylinder_001"));
	Tripod2_Cylinder_001->SetupAttachment(compTirpodDown);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempTripod2_Cylinder_001(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/Tripod/Resource/Tripod2_Cylinder_001.Tripod2_Cylinder_001'"));
	if (tempTripod2_Cylinder_001.Succeeded())
	{
		Tripod2_Cylinder_001->SetStaticMesh(tempTripod2_Cylinder_001.Object);
	}

	//Tripod2_Beine-----------------------
	Tripod2_Beine = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tripod2_Beine"));
	Tripod2_Beine->SetupAttachment(compTirpodDown);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempTripod2_Beine(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/Tripod/Resource/Tripod2_Beine.Tripod2_Beine'"));
	if (tempTripod2_Beine.Succeeded())
	{
		Tripod2_Beine->SetStaticMesh(tempTripod2_Beine.Object);
	}
	//Tripod2_Beine_001-----------------------
	Tripod2_Beine_001 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tripod2_Beine_001"));
	Tripod2_Beine_001->SetupAttachment(compTirpodDown);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempTripod2_Beine_001(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/Tripod/Resource/Tripod2_Beine_001.Tripod2_Beine_001'"));
	if (tempTripod2_Beine_001.Succeeded())
	{
		Tripod2_Beine_001->SetStaticMesh(tempTripod2_Beine_001.Object);
	}
	//Tripod2_Beine_002-----------------------
	Tripod2_Beine_002 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tripod2_Beine_002"));
	Tripod2_Beine_002->SetupAttachment(compTirpodDown);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempTripod2_Beine_002(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/Tripod/Resource/Tripod2_Beine_002.Tripod2_Beine_002'"));
	if (tempTripod2_Beine_002.Succeeded())
	{
		Tripod2_Beine_002->SetStaticMesh(tempTripod2_Beine_002.Object);
	}
	//Tripod2_Cone-----------------------
	Tripod2_Cone = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tripod2_Cone"));
	Tripod2_Cone->SetupAttachment(compTirpodDown);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempTripod2_Cone(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/Tripod/Resource/Tripod2_Cone.Tripod2_Cone'"));
	if (tempTripod2_Cone.Succeeded())
	{
		Tripod2_Cone->SetStaticMesh(tempTripod2_Cone.Object);
	}
	//Tripod2_Cone_001-----------------------
	Tripod2_Cone_001 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tripod2_Cone_001"));
	Tripod2_Cone_001->SetupAttachment(compTirpodDown);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempTripod2_Cone_001(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/Tripod/Resource/Tripod2_Cone_001.Tripod2_Cone_001'"));
	if (tempTripod2_Cone_001.Succeeded())
	{
		Tripod2_Cone_001->SetStaticMesh(tempTripod2_Cone_001.Object);
	}
	//Tripod2_Cone_002-----------------------
	Tripod2_Cone_002 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tripod2_Cone_002"));
	Tripod2_Cone_002->SetupAttachment(compTirpodDown);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempTripod2_Cone_002(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/Tripod/Resource/Tripod2_Cone_002.Tripod2_Cone_002'"));
	if (tempTripod2_Cone_002.Succeeded())
	{
		Tripod2_Cone_002->SetStaticMesh(tempTripod2_Cone_002.Object);
	}
	//Tripod2_Griffel-----------------------
	Tripod2_Griffel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tripod2_Griffel"));
	Tripod2_Griffel->SetupAttachment(compTirpodDown);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempTripod2_Griffel(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/Tripod/Resource/Tripod2_Griffel.Tripod2_Griffel'"));
	if (tempTripod2_Griffel.Succeeded())
	{
		Tripod2_Griffel->SetStaticMesh(tempTripod2_Griffel.Object);
	}
	//Tripod2_Griffel_001-----------------------
	Tripod2_Griffel_001 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tripod2_Griffel_001"));
	Tripod2_Griffel_001->SetupAttachment(compTirpodDown);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempTripod2_Griffel_001(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/Tripod/Resource/Tripod2_Griffel_001.Tripod2_Griffel_001'"));
	if (tempTripod2_Griffel_001.Succeeded())
	{
		Tripod2_Griffel_001->SetStaticMesh(tempTripod2_Griffel_001.Object);
	}
	//Tripod2_Griffel_002-----------------------
	Tripod2_Griffel_002 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tripod2_Griffel_002"));
	Tripod2_Griffel_002->SetupAttachment(compTirpodDown);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempTripod2_Griffel_002(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/Tripod/Resource/Tripod2_Griffel_002.Tripod2_Griffel_002'"));
	if (tempTripod2_Griffel_002.Succeeded())
	{
		Tripod2_Griffel_002->SetStaticMesh(tempTripod2_Griffel_002.Object);
	}
	//Tripod2_Griffel_003-----------------------
	Tripod2_Griffel_003 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tripod2_Griffel_003"));
	Tripod2_Griffel_003->SetupAttachment(compTirpodDown);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempTripod2_Griffel_003(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/Tripod/Resource/Tripod2_Griffel_003.Tripod2_Griffel_003'"));
	if (tempTripod2_Griffel_003.Succeeded())
	{
		Tripod2_Griffel_003->SetStaticMesh(tempTripod2_Griffel_003.Object);
	}
	//Tripod2_Griffel_004-----------------------
	Tripod2_Griffel_004 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tripod2_Griffel_004"));
	Tripod2_Griffel_004->SetupAttachment(compTirpodDown);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempTripod2_Griffel_004(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/Tripod/Resource/Tripod2_Griffel_004.Tripod2_Griffel_004'"));
	if (tempTripod2_Griffel_004.Succeeded())
	{
		Tripod2_Griffel_004->SetStaticMesh(tempTripod2_Griffel_004.Object);
	}
	//Tripod2_Griffel_005-----------------------
	Tripod2_Griffel_005 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tripod2_Griffel_005"));
	Tripod2_Griffel_005->SetupAttachment(compTirpodDown);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempTripod2_Griffel_005(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/Tripod/Resource/Tripod2_Griffel_005.Tripod2_Griffel_005'"));
	if (tempTripod2_Griffel_005.Succeeded())
	{
		Tripod2_Griffel_005->SetStaticMesh(tempTripod2_Griffel_005.Object);
	}
	//Tripod2_Griffel_006-----------------------
	Tripod2_Griffel_006 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tripod2_Griffel_006"));
	Tripod2_Griffel_006->SetupAttachment(compTirpodDown);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempTripod2_Griffel_006(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/Tripod/Resource/Tripod2_Griffel_006.Tripod2_Griffel_006'"));
	if (tempTripod2_Griffel_006.Succeeded())
	{
		Tripod2_Griffel_006->SetStaticMesh(tempTripod2_Griffel_006.Object);
	}
	//Tripod2_Griffel_007-----------------------
	Tripod2_Griffel_007 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tripod2_Griffel_007"));
	Tripod2_Griffel_007->SetupAttachment(compTirpodDown);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempTripod2_Griffel_007(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/Tripod/Resource/Tripod2_Griffel_007.Tripod2_Griffel_007'"));
	if (tempTripod2_Griffel_007.Succeeded())
	{
		Tripod2_Griffel_007->SetStaticMesh(tempTripod2_Griffel_007.Object);
	}
	//Tripod2_Griffel_008-----------------------
	Tripod2_Griffel_008 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tripod2_Griffel_008"));
	Tripod2_Griffel_008->SetupAttachment(compTirpodDown);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempTripod2_Griffel_008(TEXT("/Script/Engine.StaticMesh'/Game/DKW/Asset/Camera/Tripod/Resource/Tripod2_Griffel_008.Tripod2_Griffel_008'"));
	if (tempTripod2_Griffel_008.Succeeded())
	{
		Tripod2_Griffel_008->SetStaticMesh(tempTripod2_Griffel_008.Object);
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
