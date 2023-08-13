// Fill out your copyright notice in the Description page of Project Settings.


#include "O_Camera_Dolly.h"

AO_Camera_Dolly::AO_Camera_Dolly()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AO_Camera_Dolly::BeginPlay()
{
	Super::BeginPlay();
}

void AO_Camera_Dolly::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AO_Camera_Dolly::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
