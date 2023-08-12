// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimLibrary.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimationAsset.h"
#include "Animation/AnimSequence.h"

void UAnimLibrary::NativeConstruct()
{
	Super::NativeConstruct();

	btn_sitOnGround->OnClicked.AddDynamic(this, &UAnimLibrary::OnClicksitOnGround);
	btn_sitOnChair->OnClicked.AddDynamic(this, &UAnimLibrary::OnClicksitOnChair);
	btn_standingTalk->OnClicked.AddDynamic(this, &UAnimLibrary::OnClickstandingTalk);
	btn_standingClap->OnClicked.AddDynamic(this, &UAnimLibrary::OnClickstandingClap);
	btn_idle->OnClicked.AddDynamic(this, &UAnimLibrary::OnClickidle);
	btn_walking->OnClicked.AddDynamic(this, &UAnimLibrary::OnClickwalking);
	btn_back->OnClicked.AddDynamic(this, &UAnimLibrary::OnClickback);


	UE_LOG(LogTemp, Warning, TEXT("Anim lib indoor!"));
	//월드상에 배치된 메타휴먼의 정보(acoter임)를 가져온다.
	//1. 월드 상에 배치된 모든 액터 정보를 배열로 받아온다.
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FoundActors);

	for (AActor* tmp : FoundActors)
	{
		if (tmp->GetName().Contains("BP_Cooper"))
		{
			goalHuman = tmp;
		}
	}
    goalHumanBody = goalHuman->FindComponentByClass<USkeletalMeshComponent>();
// 	if(goalHumanBody!=nullptr)UE_LOG(LogTemp,Warning,TEXT("Find Success !! Human Body"));
	

}

int32 UAnimLibrary::GetAnimInfo()
{
	return selectedAnim;
}

void UAnimLibrary::SetAnimPlayTime(float val)
{
	animPlayTime = val;
}

void UAnimLibrary::OnClicksitOnGround()
{
	
	// 	//눌린 버튼에 해당하는 MarkEditor 이미지와 텍스트를 업데이트한다.
 	selectedAnim = 1;
	//UAnimInstance* ai = goalHumanBody->GetAnimInstance();
	AnimationToPlay = nullptr;
	AnimationToPlay = Cast<UAnimSequence>(
		StaticLoadObject(UAnimSequence::StaticClass(), NULL, TEXT("/Script/Engine.AnimSequence'/Game/LHJ/Anim/MetaHuman/MH_MA_Sitting_Idle_Anim.MH_MA_Sitting_Idle_Anim'")));
	if (AnimationToPlay != nullptr)
	{
		//UAnimSequence* AnimationToPlay = AnimationAsset.Object;
	

		// 애니메이션 재생
		goalHumanBody->PlayAnimation(AnimationToPlay, false);
		//goalHumanBody->SetPlayRate(animPlayTime); 
	}
	else
		return;
}

void UAnimLibrary::OnClicksitOnChair()
{
	selectedAnim = 2;
	AnimationToPlay = nullptr;
	AnimationToPlay = Cast<UAnimSequence>(
		StaticLoadObject(UAnimSequence::StaticClass(), NULL, TEXT("/Script/Engine.AnimSequence'/Game/LHJ/Anim/MetaHuman/MH_MA_Sitting_Anim.MH_MA_Sitting_Anim'")));
	if (AnimationToPlay != nullptr)
	{
		//UAnimSequence* AnimationToPlay = AnimationAsset.Object;
		
		// 애니메이션 재생
		goalHumanBody->PlayAnimation(AnimationToPlay, false);
	}
	else
		return;
}

void UAnimLibrary::OnClickstandingTalk()
{
	selectedAnim = 3;
	AnimationToPlay = nullptr;
	AnimationToPlay = Cast<UAnimSequence>(
		StaticLoadObject(UAnimSequence::StaticClass(), NULL, TEXT("/Script/Engine.AnimSequence'/Game/LHJ/Anim/MetaHuman/MH_MA_Standing_Arguing.MH_MA_Standing_Arguing'")));
	if (AnimationToPlay != nullptr)
	{
		//UAnimSequence* AnimationToPlay = AnimationAsset.Object;
		
		// 애니메이션 재생
		goalHumanBody->PlayAnimation(AnimationToPlay, false);
	}
	else
		return;
}

void UAnimLibrary::OnClickstandingClap()
{
	selectedAnim = 4;
	AnimationToPlay = nullptr;
	AnimationToPlay = Cast<UAnimSequence>(
		StaticLoadObject(UAnimSequence::StaticClass(), NULL, TEXT("/Script/Engine.AnimSequence'/Game/LHJ/Anim/MetaHuman/MH_MA_Standing_Clap.MH_MA_Standing_Clap'")));
	if (AnimationToPlay != nullptr)
	{
		//UAnimSequence* AnimationToPlay = AnimationAsset.Object;

		// 애니메이션 재생
		goalHumanBody->PlayAnimation(AnimationToPlay, false);
	}
	else
		return;
}

void UAnimLibrary::OnClickidle()
{
	selectedAnim = 5;
	AnimationToPlay = nullptr;
	AnimationToPlay = Cast<UAnimSequence>(
		StaticLoadObject(UAnimSequence::StaticClass(), NULL, TEXT("/Script/Engine.AnimSequence'/Game/LHJ/Anim/MetaHuman/MH_Standing_W_Briefcase_Idle.MH_Standing_W_Briefcase_Idle'")));
	if (AnimationToPlay != nullptr)
	{
		//UAnimSequence* AnimationToPlay = AnimationAsset.Object;

		// 애니메이션 재생
		goalHumanBody->PlayAnimation(AnimationToPlay, false);
	}
	else
		return;
}

void UAnimLibrary::OnClickwalking()
{
	selectedAnim = 6;
	AnimationToPlay = nullptr;
	AnimationToPlay = Cast<UAnimSequence>(
		StaticLoadObject(UAnimSequence::StaticClass(), NULL, TEXT("/Script/Engine.AnimSequence'/Game/LHJ/Anim/MetaHuman/MH_MA_Walking_Anim1.MH_MA_Walking_Anim1'")));
	if (AnimationToPlay != nullptr)
	{
		//UAnimSequence* AnimationToPlay = AnimationAsset.Object;

		// 애니메이션 재생
		goalHumanBody->PlayAnimation(AnimationToPlay, false);
	}
	else
		return;
}

void UAnimLibrary::OnClickback()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}

