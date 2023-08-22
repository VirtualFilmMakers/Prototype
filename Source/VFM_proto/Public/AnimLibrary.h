// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AnimLibrary.generated.h"

/**
 * 
 */
UCLASS()
class VFM_PROTO_API UAnimLibrary : public UUserWidget
{
	GENERATED_BODY()

public:

	TArray<AActor*> FoundActors; //월드상에 배치된 모든 액터 정보를 저장할 배열
	UPROPERTY()
	int32 selectedAnim=5;
	
	UPROPERTY()
	AActor* goalHuman;
	
	UPROPERTY()
	UAnimSequence* AnimationToPlay[10];
	
	UPROPERTY()
	float animPlayTime=1;
	
	UPROPERTY()
	APlayerController* pc;
		
	UPROPERTY()
	class USkeletalMeshComponent* goalHumanBody;
	
	
	/*--------Bind Property-------*/
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* text_sitOnGround;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget), Category=MySettings)
	class UButton* btn_sitOnGround;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget), Category=MySettings)
	class UButton* btn_sitOnChair;
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget), Category=MySettings)
	class UButton* btn_standingTalk;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget), Category=MySettings)
	class UButton* btn_standingClap;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget), Category=MySettings)
	class UButton* btn_idle;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget), Category=MySettings)
	class UButton* btn_walking;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget), Category=MySettings)
	class UButton* btn_back;

	

	/*---Ordinary Func-----*/
	UFUNCTION()
	int32 GetAnimInfo();
	UFUNCTION()
	void SetAnimPlayTime(float val);
	UFUNCTION()
	UAnimSequence* GetAnimSequence(int idx);

	
	/*---Bind Func-----*/
	UFUNCTION()
	void OnClicksitOnGround();

	UFUNCTION()
	void OnClicksitOnChair();

	UFUNCTION()
	void OnClickstandingTalk();

	UFUNCTION()
	void OnClickstandingClap();

	UFUNCTION()
	void OnClickidle();

	UFUNCTION()
	void OnClickwalking();

	UFUNCTION()
	void OnClickback();

protected:
	virtual void NativeConstruct() override;
	
};
