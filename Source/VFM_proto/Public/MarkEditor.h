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
	int32 Animindex; //������ �ִϸ��̼��� �ε��� ��
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector ActorLocation; // ���� ������ ��ġ

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FRotator ActorRotation; //���� ������ �����̼� ��

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
	int32 MarkNumber = 0; //�� Mark ����
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
	class AMHActorA* CurrActor; //���� actor

	

//�ִϸ��̼� ���̺귯�� �ѱ� ���� ��ư
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget), Category=MySettings)
	class UButton* btn_animSelection;

	//Mark �߰���ư
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget), Category=MySettings)
	class UButton* btn_addMark;
	
	// ���� Mark
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget), Category=MySettings)
	class UButton* btn_after;

	//���� Mark
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget), Category=MySettings)
	class UButton* btn_before;

	//��ü Mark ��ȸ
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget), Category=MySettings)
	class UButton* btn_markStart;
	
	//
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
	UPROPERTY(EditAnywhere, Category = Spawn)
	TSubclassOf<class AActor> SpawnActor;  //ADD MARK�� ���� �����Ǵ� hologram's Spawn Actor

	UPROPERTY()
	class UMarkEditor* MarkEditorWidget; //�޾ƿ� Ŭ���� ������ ���� MakrEditorWidget�� ������. ���� ������ ������ ����
	UPROPERTY()	
	class UAnimLibrary* AnimLibWidget; //�޾ƿ� Ŭ���� ������ ���� AnimWidget�� ������. ���� ������ ������ ����


	/*------------*/
	UPROPERTY()
	TArray<FAnimSavedStruct> AnimSavedArray;
	//���� Mark�� animation index, location, dirction�� ������ ����ü �迭


	UFUNCTION()
	void SetCurrActor(AMHActorA* temp);
	
	UFUNCTION()
	void OnClickAnimLib(); // MarkEditor���� animlib �޴��� ���������� ������ �Լ�
	
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
