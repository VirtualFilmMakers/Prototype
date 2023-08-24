// Fill out your copyright notice in the Description page of Project Settings.


#include "O_BuildSystem.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "OSY_TESTCharacter.h"
#include "O_SpawnActor.h"

UO_BuildSystem::UO_BuildSystem()
{
	PrimaryComponentTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UInputAction> tempBuildPlace(TEXT("//Script/EnhancedInput.InputAction'/Game/OSY/Inputs/IA_OSY_BuildPlace.IA_OSY_BuildPlace'"));
	if (tempBuildPlace.Succeeded())
	{
		ia_BuildPlace1 = tempBuildPlace.Object;
	}

}

void UO_BuildSystem::BeginPlay()
{
	Super::BeginPlay();

	me = Cast<AOSY_TESTCharacter>(GetOwner());

}

void UO_BuildSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UO_BuildSystem::SetupInputBinding(class UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* BuildInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (BuildInput)
	{

		BuildInput->BindAction(ia_BuildPreview1, ETriggerEvent::Triggered, this, &UO_BuildSystem::BuildPreview1);
		BuildInput->BindAction(ia_BuildPlace1, ETriggerEvent::Started, this, &UO_BuildSystem::BuildPlace1);
		BuildInput->BindAction(ia_BuildPreview2, ETriggerEvent::Triggered, this, &UO_BuildSystem::BuildPreview2);
		BuildInput->BindAction(ia_BuildPlace2, ETriggerEvent::Started, this, &UO_BuildSystem::BuildPlace2);
	}
}

void UO_BuildSystem::BuildPreview1()
{
	FVector BPWorldLocation;
	FVector BPWorldDirection;

	// BPWorldLocation�� BPWorldDirection�� ��� ������� ���� ������ �ʿ��� �� �ֽ��ϴ�.
	// ���� ���, �÷��̾� ��ġ�� �ü� ������ BPWorldLocation�� BPWorldDirection�� �Ҵ��ϴ� ���� ������� ó���� �� �ֽ��ϴ�.

	FVector EndPoint = BPWorldLocation + BPWorldDirection * 3000; // �������� ���� ���

	DrawDebugLine(GetWorld(), BPWorldLocation, EndPoint, FColor::Green, false, -1, 0, 10);
}

void UO_BuildSystem::BuildPlace1()
{
	FVector BPWorldLocation;
	FVector BPWorldDirection;

	FVector2D BScreenPosition;
	me->pc->GetMousePosition(BScreenPosition.X, BScreenPosition.Y);
	me->pc->DeprojectScreenPositionToWorld(BScreenPosition.X, BScreenPosition.Y, BPWorldLocation, BPWorldDirection);
	BuildPreview1();
	ServerBuildPlace1(BPWorldLocation, BPWorldDirection);
	MulticastBuildPlace1(BPWorldLocation, BPWorldDirection);
}

void UO_BuildSystem::ServerBuildPlace1_Implementation(const FVector& bLocation, const FVector& bDirection)
{
	FVector BstartLocation = bLocation;
	FVector BendLocation = bLocation + bDirection * 3000;

	FHitResult BhitResult;
	FCollisionQueryParams BCollisionParam;
	bool bHit = GetWorld()->LineTraceSingleByChannel(BhitResult, BstartLocation, BendLocation, ECC_Visibility, BCollisionParam);
	UE_LOG(LogTemp, Warning, TEXT("Bhit result : %s"), bHit ? *FString("true") : *FString("false"));

	FVector SpawnLocation = bHit ? BhitResult.Location : BendLocation;
	bool bCanSpawn = true;

	if (bCanSpawn)
	{
		// ���� �׸��� ũ�⿡ ���� ����
		FVector GridCellSize = FVector(100.0f, 100.0f, 100.0f); // ���� �׸����� �� ���� ũ�� (X, Y, Z)
		FVector AdjustedLocation = FVector(
			FMath::GridSnap(SpawnLocation.X, GridCellSize.X),
			FMath::GridSnap(SpawnLocation.Y, GridCellSize.Y),
			FMath::GridSnap(SpawnLocation.Z, GridCellSize.Z)
		);

		FRotator SpawnRotation = FRotator::ZeroRotator;
		FActorSpawnParameters BuildParam;
		BuildParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AO_SpawnActor* SpawnedActor = GetWorld()->SpawnActor<AO_SpawnActor>(FloorFactory, AdjustedLocation, SpawnRotation, BuildParam);

		UE_LOG(LogTemp, Warning, TEXT("BHere?"));
	}

}

void UO_BuildSystem::MulticastBuildPlace1_Implementation(const FVector& bLocation, const FVector& bDirection)
{
	FVector BstartLocation = bLocation;
	FVector BendLocation = bLocation + bDirection * 3000;

	FHitResult BhitResult;
	FCollisionQueryParams BCollisionParam;
	bool bHit = GetWorld()->LineTraceSingleByChannel(BhitResult, BstartLocation, BendLocation, ECC_Visibility, BCollisionParam);
	UE_LOG(LogTemp, Warning, TEXT("Bhit result : %s"), bHit ? *FString("true") : *FString("false"));

	FVector SpawnLocation = bHit ? BhitResult.Location : BendLocation;
	bool bCanSpawn = true;

	if (bCanSpawn)
	{
		// ���� �׸��� ũ�⿡ ���� ����
		FVector GridCellSize = FVector(100.0f, 100.0f, 100.0f); // ���� �׸����� �� ���� ũ�� (X, Y, Z)
		FVector AdjustedLocation = FVector(
			FMath::GridSnap(SpawnLocation.X, GridCellSize.X),
			FMath::GridSnap(SpawnLocation.Y, GridCellSize.Y),
			FMath::GridSnap(SpawnLocation.Z, GridCellSize.Z)
		);

		FRotator SpawnRotation = FRotator::ZeroRotator;
		FActorSpawnParameters BuildParam;
		BuildParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AO_SpawnActor* SpawnedActor = GetWorld()->SpawnActor<AO_SpawnActor>(FloorFactory, AdjustedLocation, SpawnRotation, BuildParam);

		UE_LOG(LogTemp, Warning, TEXT("BHere?"));
	}
}

void UO_BuildSystem::BuildPreview2()
{

}

void UO_BuildSystem::BuildPlace2()
{

}

void UO_BuildSystem::ServerBuildPlace2_Implementation(const FVector& bLocation, const FVector& bDirection)
{

}

void UO_BuildSystem::MulticastBuildPlace2_Implementation(const FVector& bLocation, const FVector& bDirection)
{

}

