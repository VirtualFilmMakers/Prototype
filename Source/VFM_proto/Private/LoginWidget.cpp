// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Slider.h"
#include "Components/EditableText.h"
#include "ON_GameInstance.h"
#include "Components/WidgetSwitcher.h"
#include "SessionInfoWidget.h"
#include "Components/ScrollBox.h"

void ULoginWidget::NativeConstruct()
{
	ogi= GetGameInstance<UON_GameInstance>();

	btn_CreateSession->OnClicked.AddDynamic(this,&ULoginWidget::OnClickCreateButton);
	btn_switchCreateSession->OnClicked.AddDynamic(this,&ULoginWidget::OnClickedSwitchCreateSession);
	btn_switchFindSession->OnClicked.AddDynamic(this,&ULoginWidget::OnClickedSwitchFindSession);
	btn_FindSession->OnClicked.AddDynamic(this,&ULoginWidget::OnClickFindButton);

	if (ogi != nullptr)
	{
		ogi->onSearchCompleted.AddDynamic(this,&ULoginWidget::AddRoomSlot);
	}
	
}

void ULoginWidget::OnClickCreateButton()
{
	if (ogi != nullptr && !edit_roomName->GetText().IsEmpty())
	{
		ogi->CreateMySession(edit_roomName->GetText());
	} 
}

void ULoginWidget::OnClickFindButton()
{
	if (ogi != nullptr)
	{
		ogi->FindOtherSession();
		sb_RoomListBox->ClearChildren();
	}
}

void ULoginWidget::OnClickedSwitchCreateSession()
{
	SwitchCanvas(1);
}

void ULoginWidget::OnClickedSwitchFindSession()
{

	SwitchCanvas(2);
}

void ULoginWidget::AddRoomSlot(FSessionSlotInfo slotInfo)
{
	//1. 슬롯 위젯을 생성하고
	sessionSlot= CreateWidget<USessionInfoWidget>(GetWorld(),sessionInfoWidget);

	if (sessionSlot != nullptr)
	{
		// 슬롯 위젯의 각 요소에 슬롯 정보를 넣는다
		sessionSlot->text_RoomName->SetText(FText::FromString(slotInfo.roomName));
		sessionSlot->text_HostName->SetText(FText::FromString(slotInfo.hostName));
		sessionSlot->text_PlayerCount->SetText(FText::FromString(slotInfo.playerCount));
		sessionSlot->text_PingSpeed->SetText(FText::AsNumber(slotInfo.pingSpeed));
		sessionSlot->sessionIndex = slotInfo.sessionIndex;
		// 생성한 슬롯 위젯을 스크롤 박스에 자식으로 추가한다

		sb_RoomListBox->AddChild(sessionSlot);

	}


}

void ULoginWidget::SwitchCanvas(int32 index)
{
	ws_SessionUISwitch->SetActiveWidgetIndex(index);
	
}
