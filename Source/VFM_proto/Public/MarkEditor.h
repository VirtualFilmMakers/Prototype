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
	UPROPERTY()
	class AOSY_TESTCharacter* player =nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 InputAnimState = 0;
	UPROPERTY()
	UTexture2D* img = nullptr;
	bool isCreated = false;
	
	UPROPERTY()
	class AMHActorA* CurrActor; //현재 액터

//애니메이션 라이브러리 켜기 위한 버튼
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
	

//배우 메타휴먼의 애니메이션 상태를 받아와 해당 상태를 위젯에 표시하기 위함
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = MySettings)
	class UTextBlock* text_animName;
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget), Category=MySettings)
	class USlider* slider_holdTime;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* text_sliderCount;

	/*----------*/

	UPROPERTY(EditAnywhere, Category = AnimLib)
	TSubclassOf<class UAnimLibrary> AnimLibClass; //Anim Library 생성을 위해 정보를 가져올 변수
	UPROPERTY(EditAnywhere, Category = Spawn)
	TSubclassOf<class AActor> SpawnActor;  //ADD MARK를 통해 생성되는 hologram's Spawn Actor

	UPROPERTY()
	class UMarkEditor* MarkEditorWidget; //받아온 클래스 정보를 통해 MakrEditorWidget을 만들자. 만든 위젯을 저장할 변수
	UPROPERTY()	
	class UAnimLibrary* AnimLibWidget; //받아온 클래스 정보를 통해 AnimWidget을 만들자. 만든 위젯을 저장할 변수



	UFUNCTION()
	void SetCurrActor(AMHActorA* temp);
	
	UFUNCTION()
	void OnClickAnimLib(); // MarkEditor에서 animlib 메뉴를 선택했을때 실행할 함수
	
	UFUNCTION()
	void OnClickAddMark();

	UFUNCTION()
	void OnSliderMoved(float value);

	

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	
};
