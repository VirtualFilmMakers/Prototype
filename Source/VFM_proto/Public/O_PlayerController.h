// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OSY_TESTCharacter.h"
#include "O_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class VFM_PROTO_API AO_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Replicated)
	class AOSY_TESTCharacter* lastPlayer; 

	
};
