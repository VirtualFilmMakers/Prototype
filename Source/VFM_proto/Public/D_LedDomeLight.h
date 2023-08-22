// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "D_LightBase.h"
#include "D_LedDomeLight.generated.h"

UCLASS()
class VFM_PROTO_API AD_LedDomeLight : public AD_LightBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AD_LedDomeLight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
