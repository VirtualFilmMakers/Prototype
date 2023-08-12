// Fill out your copyright notice in the Description page of Project Settings.


#include "D_LedDomeLight.h"

// Sets default values
AD_LedDomeLight::AD_LedDomeLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AD_LedDomeLight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AD_LedDomeLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

