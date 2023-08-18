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
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputMappingContext.h>
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputAction.h>
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"

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

	//카메라 할당---------------------------------------
	playerCam = CreateDefaultSubobject<UCameraComponent>(TEXT("playerCam"));
	playerCam->SetupAttachment(springArmComp);
	playerCam->FieldOfView = 30.60f;

	ConstructorHelpers::FObjectFinder<UInputMappingContext>tempInputMapping(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/OSY/Inputs/IMC_OSY_Player.IMC_OSY_Player'"));
	if(tempInputMapping.Succeeded())
	{
		InputMapping=tempInputMapping.Object;
	}

	
	

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
	pc = GetWorld()->GetFirstPlayerController();
	pc->SetShowMouseCursor(true);

}

// Called every frame
void AOSY_TESTCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	LineTraceFire();
	

}

// Called to bind functionality to input
void AOSY_TESTCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//LHJ -> 마우스 오른쪽버튼 이벤트 바인딩
	PlayerInputComponent->BindAction("PlaceMark", IE_Pressed,this, &AOSY_TESTCharacter::RightMouse);

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



//LHJ ->오른쪽 마우스 클릭 시 발동될 이벤트
void AOSY_TESTCharacter::RightMouse()
{
	bool IsHitResult;
	FHitResult HitResult;
	FVector2D MouseScreenPos;
	pc->GetMousePosition(MouseScreenPos.X,MouseScreenPos.Y);


	FVector WorldLocation;
	FVector WorldDirection;
	if (pc->DeprojectMousePositionToWorld(WorldLocation,WorldDirection))
	{
		FVector TraceStart = WorldLocation;
		FVector TraceEnd = TraceStart + WorldDirection*10000.0f;
		FCollisionQueryParams param;
		IsHitResult = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, param);
		if(IsHitResult)
		{
			UE_LOG(LogTemp,Warning,TEXT("Ray hit!!"));
			AddMarkLocation = HitResult.ImpactPoint;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Ray hit fail..."));
		}

		//LineTrace draw
		if (true)
		{
			FColor DrawColor = IsHitResult ? FColor::Green : FColor::Red;
			const float DebugLifeTime  = 5.0f;
			DrawDebugLine(GetWorld(),TraceStart,TraceEnd,DrawColor,false, DebugLifeTime);
		} //라인트레이스 모습 그려주세용
		//에디터 안켜졌는데도 쏘는 레이에 맞춰 메타휴먼이 생겨남.
		//모드 설정이 필요할듯?
	}

		
}



void AOSY_TESTCharacter::CameraZoom(float value)
{
	float NewTargetArmLength = springArmComp->TargetArmLength + value * ZoomStep;
	springArmComp->TargetArmLength = FMath::Clamp(NewTargetArmLength, MinZoomLength, MaxZoomLength);
}

void AOSY_TESTCharacter::LineTraceFire()
{
	
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
		//APlayerController* NewController = Cast<APlayerController>(testPawn->GetController());
		APlayerController* NewController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		//APlayerController* NewController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (NewController)
		{
			NewController->Possess((APawn*)testPawn);
		}
	}
}

void AOSY_TESTCharacter::ChangePosses(ACharacter* NewPawn)
{
	if (NewPawn)
	{
		
	}
}