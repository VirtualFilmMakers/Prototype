// Fill out your copyright notice in the Description page of Project Settings.


#include "O_PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Net/UnrealNetwork.h"// �𸮾� ��Ʈ��ũ ��� ����� ���� ���

void AO_PlayerController::BeginPlay()
{
	Super::BeginPlay();
// 
//     ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder(TEXT("/Game/OSY/UI/BP_InGameWidget_C"));
//     if (WidgetClassFinder.Succeeded())
//     {
//         // ���� �ν��Ͻ��� �����ϰ� ȭ�鿡 �߰��մϴ�.
//         UUserWidget* WidgetInstance = CreateWidget<UUserWidget>(this, WidgetClassFinder.Class);
//         if (WidgetInstance)
//         {
//             // ������ ȭ�鿡 �߰��մϴ�.
//             WidgetInstance->AddToViewport();
//         }
//     }
}

void AO_PlayerController::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AO_PlayerController, lastPlayer);
}
