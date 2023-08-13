// Fill out your copyright notice in the Description page of Project Settings.


#include "O_Camera_Dron.h"

AO_Camera_Dron::AO_Camera_Dron()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AO_Camera_Dron::BeginPlay()
{
	Super::BeginPlay();
}

void AO_Camera_Dron::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AO_Camera_Dron::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
