// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginWidget.generated.h"


UCLASS()
class VFM_PROTO_API ULoginWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct()override;

public:
	class UON_GameInstance* ogi;

	// Canvas_Main---------------------------
	UPROPERTY(VisibleAnywhere,meta=(BindWidget),Category= "MySettigs")
	class UWidgetSwitcher* ws_SessionUISwitch;

	UPROPERTY(VisibleAnywhere,meta=(BindWidget),Category= "MySettigs")
	class UTextBlock* text_programName;

	UPROPERTY(VisibleAnywhere,meta=(BindWidget),Category= "MySettigs")
	class UButton* btn_switchCreateSession;

	UPROPERTY(VisibleAnywhere,meta=(BindWidget),Category= "MySettigs")
	class UButton* btn_switchFindSession;

	UPROPERTY(VisibleAnywhere,meta=(BindWidget),Category= "MySettigs")
	class UButton* btn_QuitToDeskTop;

	// Canvas_Create---------------------------
	UPROPERTY(VisibleAnywhere,meta=(BindWidget),Category= "MySettigs")
	class UEditableText* edit_roomName;
	
	UPROPERTY(VisibleAnywhere,meta=(BindWidget),Category= "MySettigs")
	class UEditableText* edit_roomExplanation;

	UPROPERTY(VisibleAnywhere,meta=(BindWidget),Category= "MySettigs")
	class UEditableText* edit_roomMax;

	UPROPERTY(VisibleAnywhere,meta=(BindWidget),Category= "MySettigs")
	class UTextBlock* text_CreateNewProject;

	UPROPERTY(VisibleAnywhere,meta=(BindWidget),Category= "MySettigs")
	class UTextBlock* text_TeamInfomation;

	UPROPERTY(VisibleAnywhere,meta=(BindWidget),Category= "MySettigs")
	class UButton* btn_CreateSession;

	UPROPERTY(VisibleAnywhere,meta=(BindWidget),Category= "MySettigs")
	class UButton* btn_BackFromCreate;

	UPROPERTY(VisibleAnywhere,meta=(BindWidget),Category= "MySettigs")
	class UButton* btn_BackFromFind;

	// Canvas_Find-------------------------

	UPROPERTY(VisibleAnywhere,meta=(BindWidget),Category= "MySettigs")
	class UScrollBox* sb_RoomListBox;

	UPROPERTY(VisibleAnywhere,meta=(BindWidget),Category= "MySettigs")
	class UButton* btn_FindSession;

	UPROPERTY(EditAnywhere,Category= "MySettigs")
	TSubclassOf<class USessionInfoWidget> sessionInfoWidget;

	UFUNCTION()
	void OnClickCreateButton();
	UFUNCTION()
	void OnClickFindButton();

	UFUNCTION()
	void OnClickedSwitchCreateSession();

	UFUNCTION()
	void OnClickedSwitchFindSession();

	UFUNCTION()
	void AddRoomSlot(struct FSessionSlotInfo slotInfo);

	UFUNCTION()
	void ChangeButtonActivation(bool bIsActivation);
	
	
private:

	UPROPERTY()
	class USessionInfoWidget* sessionSlot;

	UFUNCTION()
	void BackToFirstCanvas();

	void SwitchCanvas(int32 index);
};
