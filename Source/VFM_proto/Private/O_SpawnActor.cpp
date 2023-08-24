// Fill out your copyright notice in the Description page of Project Settings.


#include "O_SpawnActor.h"

// Sets default values
AO_SpawnActor::AO_SpawnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AO_SpawnActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AO_SpawnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

