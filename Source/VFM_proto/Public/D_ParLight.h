// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "D_LightBase.h"
#include "D_ParLight.generated.h"

/**
 * 
 */
UCLASS()
class VFM_PROTO_API AD_ParLight : public AD_LightBase
{
	GENERATED_BODY()
	
	void SetSoureLightToControlWidget();

};
