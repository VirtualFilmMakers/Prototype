// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginWidget.generated.h"

/**
 * 
 */
UCLASS()
class VFM_PROTO_API ULoginWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct()override;

public:
	
	UPROPERTY(VisibleAnywhere,meta=(BindWidget),Category= "MySettigs")
	class UEditableText* edit_roomName;

	UPROPERTY(VisibleAnywhere,meta=(BindWidget),Category= "MySettigs")
	class UTextBlock* text_programName;

	UPROPERTY(VisibleAnywhere,meta=(BindWidget),Category= "MySettigs")
	class UButton* btn_CreateSession;

	UPROPERTY(VisibleAnywhere,meta=(BindWidget),Category= "MySettigs")
	class UButton* btn_OpenSession;

	UPROPERTY(VisibleAnywhere,meta=(BindWidget),Category= "MySettigs")
	class UButton* btn_QuitToDeskTop;

	class UON_GameInstance* ogi;

	UFUNCTION()
	void OnClickCreateButton();
	
};
