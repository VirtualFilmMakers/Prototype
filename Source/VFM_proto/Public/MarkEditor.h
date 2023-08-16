// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../VFM_proto/Public/D_ControlPanelInterface.h"
#include "MarkEditor.generated.h"



UCLASS()
class VFM_PROTO_API UMarkEditor : public UUserWidget, public ID_ControlPanelInterface
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	UWorld* World = nullptr;
	UPROPERTY()
	APlayerController* pc = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 InputAnimState = 0;
	UPROPERTY()
	UTexture2D* img = nullptr;
	bool isCreated = false;

//�ִϸ��̼� ���̺귯�� �ѱ� ���� ��ư
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget), Category=MySettings)
	class UButton* btn_animSelection;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget), Category=MySettings)
	class UButton* btn_addMark;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget), Category=MySettings)
	class UButton* btn_after;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget), Category=MySettings)
	class UButton* btn_before;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget), Category=MySettings)
	class UButton* btn_markStart;
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget), Category=MySettings)
	class UCheckBox* box_isLoop;
	

//��� ��Ÿ�޸��� �ִϸ��̼� ���¸� �޾ƿ� �ش� ���¸� ������ ǥ���ϱ� ����
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = MySettings)
	class UTextBlock* text_animName;
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget), Category=MySettings)
	class USlider* slider_holdTime;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* text_sliderCount;

	/*----------*/

	UPROPERTY(EditAnywhere, Category = AnimLib)
	TSubclassOf<class UAnimLibrary> AnimLibClass; //Anim Library ������ ���� ������ ������ ����

	UPROPERTY()
	class UMarkEditor* MarkEditorWidget; //�޾ƿ� Ŭ���� ������ ���� MakrEditorWidget�� ������. ���� ������ ������ ����
	UPROPERTY()
	class UAnimLibrary* AnimLibWidget; //�޾ƿ� Ŭ���� ������ ���� AnimWidget�� ������. ���� ������ ������ ����




	
	UFUNCTION()
	void OnClickAnimLib(); // MarkEditor���� animlib �޴��� ���������� ������ �Լ�
	
	UFUNCTION()
	void OnSliderMoved(float value);


protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	
};
