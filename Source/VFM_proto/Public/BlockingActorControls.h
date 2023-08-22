// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BlockingActorControls.generated.h"

/**
 * 
 */
UCLASS()
class VFM_PROTO_API UBlockingActorControls : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget), Category=MySettings)
	class UButton* btn_addMark;


	UFUNCTION()
	void OnClickAddMark(); // MarkEditor에서 animlib 메뉴를 선택했을때 실행할 함수
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
};
