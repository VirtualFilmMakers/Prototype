// Fill out your copyright notice in the Description page of Project Settings.


#include "O_Camera_Crane.h"

AO_Camera_Crane::AO_Camera_Crane()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AO_Camera_Crane::BeginPlay()
{
	Super::BeginPlay();
}

void AO_Camera_Crane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AO_Camera_Crane::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
