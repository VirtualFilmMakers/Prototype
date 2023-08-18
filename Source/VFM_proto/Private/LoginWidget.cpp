// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Slider.h"
#include "Components/EditableText.h"
#include "ON_GameInstance.h"

void ULoginWidget::NativeConstruct()
{
	ogi= GetGameInstance<UON_GameInstance>();

	btn_CreateSession->OnClicked.AddDynamic(this,&ULoginWidget::OnClickCreateButton);
	
}

void ULoginWidget::OnClickCreateButton()
{
	if (ogi != nullptr && !edit_roomName->GetText().IsEmpty())
	{
		ogi->CreateMySession(edit_roomName->GetText());
	} 
}
