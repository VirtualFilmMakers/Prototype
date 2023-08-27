// Fill out your copyright notice in the Description page of Project Settings.


#include "O_PlayerController.h"
#include "Net/UnrealNetwork.h"// 언리얼 네트워크 기능 사용을 위한 헤더

void AO_PlayerController::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AO_PlayerController, lastPlayer);
}
