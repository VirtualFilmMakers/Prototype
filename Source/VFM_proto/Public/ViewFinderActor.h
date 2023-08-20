// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ViewFinderActor.generated.h"

UCLASS()
class VFM_PROTO_API AViewFinderActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AViewFinderActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere,Category="MySettings")
	class UBoxComponent* boxComp;
	UPROPERTY(VisibleAnywhere,Category="MySettings")
	class UStaticMeshComponent* meshComp;
};
