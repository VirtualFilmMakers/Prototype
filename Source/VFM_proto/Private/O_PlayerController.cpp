// Fill out your copyright notice in the Description page of Project Settings.


#include "O_PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Net/UnrealNetwork.h"// 언리얼 네트워크 기능 사용을 위한 헤더

void AO_PlayerController::BeginPlay()
{
	Super::BeginPlay();
// 
//     ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder(TEXT("/Game/OSY/UI/BP_InGameWidget_C"));
//     if (WidgetClassFinder.Succeeded())
//     {
//         // 위젯 인스턴스를 생성하고 화면에 추가합니다.
//         UUserWidget* WidgetInstance = CreateWidget<UUserWidget>(this, WidgetClassFinder.Class);
//         if (WidgetInstance)
//         {
//             // 위젯을 화면에 추가합니다.
//             WidgetInstance->AddToViewport();
//         }
//     }
}

void AO_PlayerController::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AO_PlayerController, lastPlayer);
}
