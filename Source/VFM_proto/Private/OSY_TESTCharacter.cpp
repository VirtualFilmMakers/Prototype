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
#include "Net/UnrealNetwork.h"// 언리얼 네트워크 기능 사용을 위한 헤더
#include "O_CameraBase.h"


// Sets default values
AOSY_TESTCharacter::AOSY_TESTCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
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

	//리플리케이트 항시 켜놓는 기능
	bReplicates= true;

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
	myLocalRole=GetLocalRole();
	myRemoteRole=GetRemoteRole();

}

// Called every frame
void AOSY_TESTCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	
	LineTraceFire();
	// 디버깅용 로그 출력
	PrintLog();
	

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

void AOSY_TESTCharacter::ChangePossessInput()
{
	
	ServerChangePossessInput();
}

void AOSY_TESTCharacter::ServerChangePossessInput_Implementation()
{
	MulticastChangePossessInput();
	
}

void AOSY_TESTCharacter::MulticastChangePossessInput_Implementation()
{
	FVector OWorldLocation;
	FVector OWorldDirection;
	FVector2D ScreenPosition;
	pc->GetMousePosition(ScreenPosition.X,ScreenPosition.Y);
	if (pc->DeprojectScreenPositionToWorld(ScreenPosition.X, ScreenPosition.Y, OWorldLocation, OWorldDirection))
	{
		FVector startLocation=OWorldLocation;
		FVector endLocation=OWorldLocation+OWorldDirection*10000;

		FHitResult hitResult;
		FCollisionQueryParams CollisionParam;
		bool bisHit= GetWorld()->LineTraceSingleByChannel(hitResult, startLocation, endLocation, ECC_Visibility, CollisionParam);
		if (bisHit)
		{
			APlayerController* NewController = GetWorld()->GetFirstPlayerController();
			if (NewController)
			{
				testPawn = Cast<AO_CameraBase>(hitResult.GetActor());
				if (testPawn)
				{
					NewController->Possess(testPawn);
				}
			}
		}
	}




// 	FVector startLocation = playerCam->GetComponentLocation();
// 	FVector endLocation = startLocation + playerCam->GetForwardVector() * 10000;
// 	FHitResult hitResult;
// 	FCollisionQueryParams CollisionParam;
// 	bool bHit = GetWorld()->LineTraceSingleByChannel(hitResult, startLocation, endLocation, ECC_Visibility,CollisionParam);
// 	DrawDebugLine(GetWorld(),startLocation,endLocation,FColor::Red,false,5.f,0,1.f);
// 
// 	if (bHit)
// 	{
// 		FString HitObjectName = hitResult.GetActor() ? hitResult.GetActor()->GetName() : FString(TEXT("None"));
// 		UE_LOG(LogTemp, Warning, TEXT("Hit object: %s"), *HitObjectName);
// 
// 		APlayerController* NewController = GetWorld()->GetFirstPlayerController();
// 		if (NewController)
// 		{
// 			APawn* PawnToPossess = Cast<APawn>(testPawn);
// 			if (PawnToPossess)
// 			{
// 				NewController->Possess(PawnToPossess);
// 			}
// 		}
// 	}

}

void AOSY_TESTCharacter::ChangePosses(ACharacter* NewPawn)
{
	if (NewPawn)
	{
		
	}
}

// 각종 정보를 화면에 출력하는 함수
void AOSY_TESTCharacter::PrintLog()
{
	const FString localRoleString= UEnum::GetValueAsString<ENetRole>(myLocalRole);
	const FString remoteRoleString= UEnum::GetValueAsString<ENetRole>(myRemoteRole);
	const FString ownerString = GetOwner() != nullptr ? GetOwner()->GetName() : FString("No Owner");
	const FString connectionString = GetNetConnection() != nullptr ? FString("Valid Connection") : FString("Invalid Connection");

	const FString printString = FString::Printf(TEXT("Local Role: %s\n Remote Role: %s\n Owner Name: %s\n Net Connection :%s"),*localRoleString,*remoteRoleString,*ownerString,*connectionString);

	DrawDebugString(GetWorld(),GetActorLocation(),printString,nullptr,FColor::White,0,true);


}
