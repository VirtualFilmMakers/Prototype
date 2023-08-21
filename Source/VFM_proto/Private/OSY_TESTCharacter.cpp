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
#include "Net/UnrealNetwork.h"// �𸮾� ��Ʈ��ũ ��� ����� ���� ���
#include "O_CameraBase.h"


// Sets default values
AOSY_TESTCharacter::AOSY_TESTCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//�������� �Ҵ�---------------------------------------
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->TargetArmLength = DefaultArmLength;
	springArmComp->SetRelativeLocation(FVector(0, 60, 70));
	springArmComp->bEnableCameraLag = true;
	springArmComp->bEnableCameraRotationLag = true;
	springArmComp->CameraLagSpeed = 2.0f;
	springArmComp->CameraRotationLagSpeed = 2.0f;

	//ī�޶� �Ҵ�---------------------------------------
	playerCam = CreateDefaultSubobject<UCameraComponent>(TEXT("playerCam"));
	playerCam->SetupAttachment(springArmComp);
	playerCam->FieldOfView = 30.60f;

	ConstructorHelpers::FObjectFinder<UInputMappingContext>tempInputMapping(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/OSY/Inputs/IMC_OSY_Player.IMC_OSY_Player'"));
	if (tempInputMapping.Succeeded())
	{
		InputMapping = tempInputMapping.Object;
	}

	//���ø�����Ʈ �׽� �ѳ��� ���
	bReplicates = true;

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

	//-----------------------------
	myLocalRole = GetLocalRole();
	myRemoteRole = GetRemoteRole();

}

// Called every frame
void AOSY_TESTCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


	LineTraceFire();
	// ������ �α� ���
	PrintLog();


}

// Called to bind functionality to input
void AOSY_TESTCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//LHJ -> ���콺 �����ʹ�ư �̺�Ʈ ���ε�
	PlayerInputComponent->BindAction("PlaceMark", IE_Pressed, this, &AOSY_TESTCharacter::RightMouse);

	UEnhancedInputComponent* SYInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (SYInput)
	{
		SYInput->BindAction(ia_Jump, ETriggerEvent::Triggered, this, &AOSY_TESTCharacter::jump);
		SYInput->BindAction(ia_Posses, ETriggerEvent::Triggered, this, &AOSY_TESTCharacter::ChangePossessInput);
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



//LHJ ->������ ���콺 Ŭ�� �� �ߵ��� �̺�Ʈ
void AOSY_TESTCharacter::RightMouse()
{
	bool IsHitResult;
	FHitResult HitResult;
	FVector2D MouseScreenPos;
	pc->GetMousePosition(MouseScreenPos.X, MouseScreenPos.Y);


	FVector WorldLocation;
	FVector WorldDirection;
	if (pc->DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
	{
		FVector TraceStart = WorldLocation;
		FVector TraceEnd = TraceStart + WorldDirection * 10000.0f;
		FCollisionQueryParams param;
		IsHitResult = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, param);
		if (IsHitResult)
		{
			UE_LOG(LogTemp, Warning, TEXT("Ray hit!!"));
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
			const float DebugLifeTime = 5.0f;
			DrawDebugLine(GetWorld(), TraceStart, TraceEnd, DrawColor, false, DebugLifeTime);
		} //����Ʈ���̽� ��� �׷��ּ���
		//������ �������µ��� ��� ���̿� ���� ��Ÿ�޸��� ���ܳ�.
		//��� ������ �ʿ��ҵ�?
	}
	if (CurrActor != nullptr)
		CurrActor->SetActorLocation(AddMarkLocation);
}



void AOSY_TESTCharacter::CameraZoom(float value)
{
	float NewTargetArmLength = springArmComp->TargetArmLength + value * ZoomStep;
	springArmComp->TargetArmLength = FMath::Clamp(NewTargetArmLength, MinZoomLength, MaxZoomLength);
}

void AOSY_TESTCharacter::LineTraceFire()
{

}

void AOSY_TESTCharacter::ChangePossessInput()
{
	FVector OWorldLocation;
	FVector OWorldDirection;
	FVector2D ScreenPosition;
	pc->GetMousePosition(ScreenPosition.X, ScreenPosition.Y);
	pc->DeprojectScreenPositionToWorld(ScreenPosition.X, ScreenPosition.Y, OWorldLocation, OWorldDirection);
	ServerChangePossessInput(OWorldLocation, OWorldDirection);

}

void AOSY_TESTCharacter::ServerChangePossessInput_Implementation(const FVector& wLocation, const FVector& wDirection)
{
	// �÷��̾ ����Ʈ���̽��� ����
	FVector startLocation = wLocation;
	FVector endLocation = wLocation + wDirection * 10000;

	FHitResult hitResult;
	FCollisionQueryParams CollisionParam;
	bool bisHit = GetWorld()->LineTraceSingleByChannel(hitResult, startLocation, endLocation, ECC_Visibility, CollisionParam);
	UE_LOG(LogTemp, Warning, TEXT("hit result : %s"), bisHit ? *FString("true") : *FString("false"));

	// ���� ī�޶��̽��� ���� �ɸ��Ͷ� �ε����ٸ�
	if (bisHit)
	{
		// �������ٰ� ������ ��û�� �Ѵ�
		NewController = GetController<APlayerController>();
		if (NewController != nullptr)
		{
			testPawn = Cast<AO_CameraBase>(hitResult.GetActor());
			UE_LOG(LogTemp, Warning, TEXT("test pawn : %s"), testPawn != nullptr ? *testPawn->GetName() : *FString("Null"));
			if (testPawn)
			{
				NewController->UnPossess();
				NewController->Possess(testPawn);
			}

		}
	}
}

void AOSY_TESTCharacter::MulticastChangePossessInput_Implementation()
{


}

void AOSY_TESTCharacter::ChangePosses(ACharacter* NewPawn)
{
	if (NewPawn)
	{

	}
}

// ���� ������ ȭ�鿡 ����ϴ� �Լ�
void AOSY_TESTCharacter::PrintLog()
{
	const FString localRoleString = UEnum::GetValueAsString<ENetRole>(myLocalRole);
	const FString remoteRoleString = UEnum::GetValueAsString<ENetRole>(myRemoteRole);
	const FString ownerString = GetOwner() != nullptr ? GetOwner()->GetName() : FString("No Owner");
	const FString connectionString = GetNetConnection() != nullptr ? FString("Valid Connection") : FString("Invalid Connection");

	const FString printString = FString::Printf(TEXT("Local Role: %s\n Remote Role: %s\n Owner Name: %s\n Net Connection :%s"), *localRoleString, *remoteRoleString, *ownerString, *connectionString);

	DrawDebugString(GetWorld(), GetActorLocation(), printString, nullptr, FColor::White, 0, true);


}

void AOSY_TESTCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AOSY_TESTCharacter, NewController);

}
