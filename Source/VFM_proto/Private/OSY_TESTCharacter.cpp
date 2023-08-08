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

// Sets default values
AOSY_TESTCharacter::AOSY_TESTCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//mesh 데이터 할당
	ConstructorHelpers::FObjectFinder<USkeletalMesh>tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Quinn_Simple.SKM_Quinn_Simple'"));
	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	}
	//스프링암 할당---------------------------------------
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->TargetArmLength = DefaultArmLength;
	springArmComp->SetRelativeLocation(FVector(0, 60, 70));
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







