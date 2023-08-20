// Fill out your copyright notice in the Description page of Project Settings.


#include "SessionInfoWidget.h"
#include "ON_GameInstance.h"
#include "Components/Button.h"

void USessionInfoWidget::NativeConstruct()
{
	ogi= GetGameInstance<UON_GameInstance>();

	btn_Join->OnClicked.AddDynamic(this,&USessionInfoWidget::OnClickedJoinButton);
}

void USessionInfoWidget::OnClickedJoinButton()
{
	if (ogi != nullptr)
	{
		ogi->JoinSelectedSession(sessionIndex);
	}
}
