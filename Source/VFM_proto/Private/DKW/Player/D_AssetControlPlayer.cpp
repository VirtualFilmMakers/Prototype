// Fill out your copyright notice in the Description page of Project Settings.


#include "D_AssetControlPlayer.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputMappingContext.h>
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputAction.h>
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h>

// Sets default values
AD_AssetControlPlayer::AD_AssetControlPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
#pragma region setup
	// context
	ConstructorHelpers::FObjectFinder<UInputMappingContext> tempIMC(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/DKW/AssetControlPlayer/AssetControlPlayerInputMappingContext.AssetControlPlayerInputMappingContext'"));
	if (tempIMC.Succeeded())
	{
		InputMappingContext = tempIMC.Object;
	}

	// IA 할당
	ConstructorHelpers::FObjectFinder<UInputAction> tempIA_Move(TEXT("/Script/EnhancedInput.InputAction'/Game/DKW/AssetControlPlayer/IA_Move_Camera.IA_Move_Camera'"));
	if (tempIA_Move.Succeeded())
	{
		ia_Move = tempIA_Move.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction> tempLook(TEXT("/Script/EnhancedInput.InputAction'/Game/DKW/AssetControlPlayer/IA_Look_Camera.IA_Look_Camera'"));
	if (tempLook.Succeeded())
	{
		ia_Look = tempLook.Object;
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
#pragma endregion

	
}

// Called when the game starts or when spawned
void AD_AssetControlPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void AD_AssetControlPlayer::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		float dt = GetWorld()->DeltaRealTimeSeconds;
		FVector dir = MovementVector.Y*FVector::ForwardVector + MovementVector.X*FVector::RightVector;

		SetActorLocation(GetActorLocation() + dt * dir*1000.f);
	}
}

void AD_AssetControlPlayer::Look(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		FRotator curRot = GetActorRotation();
		FVector2D LookValue = Value.Get<FVector2D>();
		if (LookValue.X != 0.f)
		{
			SetActorRotation(FRotator(curRot.Pitch, curRot.Yaw + LookValue.X, curRot.Roll ));
			//AddControllerYawInput(LookValue.X);
		}
		if (LookValue.Y != 0.f)
		{
			SetActorRotation(FRotator(curRot.Pitch + LookValue.Y, curRot.Yaw, curRot.Roll));
			//AddControllerPitchInput(LookValue.Y);
		}
	}
}

// Called every frame
void AD_AssetControlPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AD_AssetControlPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (Input)
	{
		Input->BindAction(ia_Move, ETriggerEvent::Triggered, this, &AD_AssetControlPlayer::Move);
		Input->BindAction(ia_Look, ETriggerEvent::Triggered, this, &AD_AssetControlPlayer::Look);
	}
}


//void AD_AssetControlPlayer::jump()
//{
//	
//}



