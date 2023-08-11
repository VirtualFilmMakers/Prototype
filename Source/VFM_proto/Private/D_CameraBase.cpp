// Fill out your copyright notice in the Description page of Project Settings.


#include "D_CameraBase.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AD_CameraBase::AD_CameraBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AD_CameraBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AD_CameraBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AD_CameraBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AD_CameraBase::PossessToCamera()
{
	APlayerController* pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (pc) {
		pc->Possess(this);
	}
}

