// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_TESTCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "OSY_PlayerAnimInstance.h"
#include "PlayerBaseComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AOSY_TESTCharacter::AOSY_TESTCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	
	//나의 메시를 루트로 세팅한다
	// 겟 캡슐을 메시에 상속한다
	 
// 	mesh 데이터 할당
 	//	ConstructorHelpers::FObjectFinder<USkeletalMesh>tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/OSY/Model/BasicCharacter.BasicCharacter'"));
// 		if (tempMesh.Succeeded())
// 		{
// 			GetMesh()->SetSkeletalMesh(tempMesh.Object);
// 		}
	//스프링암 할당---------------------------------------
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->TargetArmLength = DefaultArmLength;
	springArmComp->SetRelativeLocation(FVector(0, 60, 70));
	springArmComp->bEnableCameraLag=true;
	springArmComp->bEnableCameraRotationLag=true;
	springArmComp->CameraLagSpeed=2.0f;
	springArmComp->CameraRotationLagSpeed=2.0f;

	//	springArmComp->TargetArmLength=
		//카메라 할당---------------------------------------
	playerCam = CreateDefaultSubobject<UCameraComponent>(TEXT("playerCam"));
	playerCam->SetupAttachment(springArmComp);
	playerCam->FieldOfView = 30.60f;

	
	

}

// Called when the game starts or when spawned
void AOSY_TESTCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}



}

// Called every frame
void AOSY_TESTCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	
	

}

// Called to bind functionality to input
void AOSY_TESTCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* SYInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (SYInput)
	{
		SYInput->BindAction(ia_Jump, ETriggerEvent::Triggered, this, &AOSY_TESTCharacter::jump);
		SYInput->BindAction(ia_Posses, ETriggerEvent::Triggered, this, &AOSY_TESTCharacter::ChangePosessInput);
	}

	onInputBindingDelegate.Broadcast(PlayerInputComponent);

}
void AOSY_TESTCharacter::Horizontal(float value)
{
	AddMovementInput(GetActorRightVector(), value);
}

void AOSY_TESTCharacter::Vertical(float value)
{
	AddMovementInput(GetActorForwardVector(), value);
}

void AOSY_TESTCharacter::jump()
{
	Jump();
}




void AOSY_TESTCharacter::CameraZoom(float value)
{
	float NewTargetArmLength = springArmComp->TargetArmLength + value * ZoomStep;
	springArmComp->TargetArmLength = FMath::Clamp(NewTargetArmLength, MinZoomLength, MaxZoomLength);
}



void AOSY_TESTCharacter::Build()
{
	FVector BstartLocation = playerCam->GetComponentLocation();
	FVector BendLocation = BstartLocation + playerCam->GetForwardVector() * 5000;
	FHitResult BHitInfo;
	FCollisionQueryParams Bparam;
	Bparam.AddIgnoredActor(this);
	bool bHit = GetWorld()->LineTraceSingleByChannel(BHitInfo, BstartLocation, BendLocation, ECC_Visibility, Bparam);
	
}

void AOSY_TESTCharacter::ChangePosessInput()
{
	FVector startLocation = playerCam->GetComponentLocation();
	FVector endLocation = startLocation + playerCam->GetForwardVector() * 5000;
	FHitResult hitInfo;
	FCollisionQueryParams param;
	param.AddIgnoredActor(this);
	bool bHit = GetWorld()->LineTraceSingleByChannel(hitInfo, startLocation, endLocation, ECC_Visibility, param);
	if (bHit)
	{
		APlayerController* NewController = UGameplayStatics::GetPlayerController(GetWorld(), 0);	
		if (NewController)
		{
			NewController->Possess(testPawn);
		}
	}
}



