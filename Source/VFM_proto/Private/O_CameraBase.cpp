// Fill out your copyright notice in the Description page of Project Settings.


#include "O_CameraBase.h"

// Sets default values
AO_CameraBase::AO_CameraBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

}

