// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../VFM_proto/Public/D_ControlPanelInterface.h"
#include "Engine/DataTable.h"
#include "MarkEditor.generated.h"


USTRUCT(BlueprintType)
struct FAnimSavedStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 Animindex; //지정된 애니메이션의 인덱스 값
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector ActorLocation; // 현재 액터의 위치

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FRotator ActorRotation; //현재 액터의 로테이션 값

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float playTime; 

	
// 	
// 	UPROPERTY()
// 	FVector 
};


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
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 MarkNumber = 0; //총 Mark 개수
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 CurrMark = 0; //Mark Pointer
	UPROPERTY()
	USkeletalMeshComponent* CurrActorSkeletal;
	float currTime = 0;
	float delTime = 0;
	FVector dir;
	bool TimeOut;
	bool TimerOn = false;
	bool EntireMode = false;
	float DistanceToTarget = 0.0f;
	bool isAdd = false;
	float SliderPlayTime = 1.0f;
	bool isArrive = false;
	bool playAnimMode = false;
	


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 InputAnimState = 0;
	UPROPERTY()
	UTexture2D* img = nullptr;
	bool isCreated = false;
	
	UPROPERTY()
	class AMHActorA* CurrActor; //현재 actor

	

//애니메이션 라이브러리 켜기 위한 버튼
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget), Category=MySettings)
	class UButton* btn_animSelection;

	//Mark 추가버튼
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget), Category=MySettings)
	class UButton* btn_addMark;
	
	// 다음 Mark
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget), Category=MySettings)
	class UButton* btn_after;

	//이전 Mark
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget), Category=MySettings)
	class UButton* btn_before;

	//전체 Mark 순회
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget), Category=MySettings)
	class UButton* btn_markStart;
	
	//
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


	/*------------*/
	UPROPERTY()
	TArray<FAnimSavedStruct> AnimSavedArray;
	//현재 Mark의 animation index, location, dirction을 저장할 구조체 배열


	UFUNCTION()
	void SetCurrActor(AMHActorA* temp);
	
	UFUNCTION()
	void OnClickAnimLib(); // MarkEditor에서 animlib 메뉴를 선택했을때 실행할 함수
	
	UFUNCTION()
	void OnClickAddMark();

	UFUNCTION()
	void OnSliderMoved(float value);

	UFUNCTION()
	void OnClickAfterMark();

	UFUNCTION()
	void OnClickBeforeMark();

	UFUNCTION()
	void OnClickEntirePlay();
	
// 	UFUNCTION()
// 	void ME_MouseRight(void);

UFUNCTION()
	float CalculateRotationDifference(FRotator CurrRot, FRotator TargetRot);

UFUNCTION()
	void RotateActorToDirection(FVector TargetDir, float RotSpeed);

public:
	UAnimSequence* WalkAnim=
	Cast<UAnimSequence>(
		StaticLoadObject(UAnimSequence::StaticClass(), NULL, TEXT("/Script/Engine.AnimSequence'/Game/LHJ/Anim/MetaHuman/MH_MA_Walking_Anim1.MH_MA_Walking_Anim1'")));


public :

/* ALL STOP Anim */
	UFUNCTION(Reliable, Server, WithValidation)
	void SpawnActorHologramServer();	
	void SpawnActorHologramServer_Implementation();
	bool SpawnActorHologramServer_Validate();

	UFUNCTION(Reliable, NetMulticast)
	void SpawnActorHologramMulticast();
	void SpawnActorHologramMulticast_Implementation();

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	
};
