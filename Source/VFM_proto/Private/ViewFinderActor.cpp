// Fill out your copyright notice in the Description page of Project Settings.


#include "ViewFinderActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AViewFinderActor::AViewFinderActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp= CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	SetRootComponent(boxComp);
	boxComp->SetGenerateOverlapEvents(true);
	boxComp->SetBoxExtent(FVector(50,32,32));
	boxComp->SetSimulatePhysics(true);
	boxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	boxComp->SetCollisionObjectType(ECC_GameTraceChannel1);
	boxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel2,ECR_Overlap);

	meshComp= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetupAttachment(RootComponent);

	bReplicates= true;
	SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void AViewFinderActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AViewFinderActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

