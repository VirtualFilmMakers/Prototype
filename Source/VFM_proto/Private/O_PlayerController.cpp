// Fill out your copyright notice in the Description page of Project Settings.


#include "O_PlayerController.h"
#include "Net/UnrealNetwork.h"// �𸮾� ��Ʈ��ũ ��� ����� ���� ���

void AO_PlayerController::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AO_PlayerController, lastPlayer);
}
