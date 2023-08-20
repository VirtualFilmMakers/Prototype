// Fill out your copyright notice in the Description page of Project Settings.


#include "O_CameraBase.h"
#include "Camera/CameraComponent.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"// 언리얼 네트워크 기능 사용을 위한 헤더

// Sets default values
AO_CameraBase::AO_CameraBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 기본 스프링암 할당
	CameraBase_SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBase_SpringArmComp"));
	//CameraBase_SpringArmComp->SetupAttachment(RootComponent);
	CameraBase_SpringArmComp->bEnableCameraLag = true;
	CameraBase_SpringArmComp->bEnableCameraRotationLag = true;
	CameraBase_SpringArmComp->CameraLagSpeed = 2.0f;
	CameraBase_SpringArmComp->CameraRotationLagSpeed = 2.0f;
	CameraBase_SpringArmComp->TargetArmLength=400;

	//기본 카메라 할당
	CameraBase_CamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraBase_CamComp"));
	CameraBase_CamComp->SetupAttachment(CameraBase_SpringArmComp);
	CameraBase_CamComp->FieldOfView = 30.60f;

	//ACamera-----------------------
	CameraBase_ACamera = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CameraBase_ACamera"));
	
	CameraBase_CamComp->SetupAttachment(CameraBase_ACamera);
	CameraBase_CamComp->SetRelativeLocation(FVector(41, 0, 4));


}

// Called when the game starts or when spawned
void AO_CameraBase::BeginPlay()
{
	Super::BeginPlay();

	
	
}

// Called every frame
void AO_CameraBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AO_CameraBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	onCameraInputBindingDelegate.Broadcast(PlayerInputComponent);
}

