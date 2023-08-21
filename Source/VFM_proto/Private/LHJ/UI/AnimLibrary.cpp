// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimLibrary.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimationAsset.h"
#include "Animation/AnimSequence.h"
#include "Components/CheckBox.h"


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


	pc = GetWorld()->GetFirstPlayerController();
	UE_LOG(LogTemp, Warning, TEXT("Anim lib indoor!"));
	//월드상에 배치된 메타휴먼의 정보(acoter임)를 가져온다.
	//1. 월드 상에 배치된 모든 액터 정보를 배열로 받아온다.
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FoundActors);

	for (AActor* tmp : FoundActors)
	{
		if (tmp->GetName().Contains("BP_Cooper"))
		{
		UE_LOG(LogTemp,Warning,TEXT("%s"),tmp);
			goalHuman = tmp;
		}
	}
    goalHumanBody = goalHuman->FindComponentByClass<USkeletalMeshComponent>();

	// Make Animation Library play
	AnimationToPlay[1] = Cast<UAnimSequence>(
		StaticLoadObject(UAnimSequence::StaticClass(), NULL, TEXT("/Script/Engine.AnimSequence'/Game/LHJ/Anim/MetaHuman/MH_MA_Sitting_Idle_Anim.MH_MA_Sitting_Idle_Anim'")));
	
	AnimationToPlay[2] = Cast<UAnimSequence>(
		StaticLoadObject(UAnimSequence::StaticClass(), NULL, TEXT("/Script/Engine.AnimSequence'/Game/LHJ/Anim/MetaHuman/MH_MA_Sitting_Anim.MH_MA_Sitting_Anim'")));
	
	AnimationToPlay[3] = Cast<UAnimSequence>(
		StaticLoadObject(UAnimSequence::StaticClass(), NULL, TEXT("/Script/Engine.AnimSequence'/Game/LHJ/Anim/MetaHuman/MH_MA_Standing_Arguing.MH_MA_Standing_Arguing'")));

	AnimationToPlay[4] = Cast<UAnimSequence>(
		StaticLoadObject(UAnimSequence::StaticClass(), NULL, TEXT("/Script/Engine.AnimSequence'/Game/LHJ/Anim/MetaHuman/MH_MA_Standing_Clap.MH_MA_Standing_Clap'")));

	AnimationToPlay[5] = Cast<UAnimSequence>(
		StaticLoadObject(UAnimSequence::StaticClass(), NULL, TEXT("/Script/Engine.AnimSequence'/Game/LHJ/Anim/MetaHuman/MH_Standing_W_Briefcase_Idle.MH_Standing_W_Briefcase_Idle'")));

	AnimationToPlay[6] = Cast<UAnimSequence>(
		StaticLoadObject(UAnimSequence::StaticClass(), NULL, TEXT("/Script/Engine.AnimSequence'/Game/LHJ/Anim/MetaHuman/MH_MA_Walking_Anim1.MH_MA_Walking_Anim1'")));

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

UAnimSequence* UAnimLibrary::GetAnimSequence(int idx)
{
	return AnimationToPlay[idx];
}

void UAnimLibrary::OnClicksitOnGround()
{
	
	// 	//눌린 버튼에 해당하는 MarkEditor 이미지와 텍스트를 업데이트한다.
 	selectedAnim = 1;
	//UAnimInstance* ai = goalHumanBody->GetAnimInstance();
	if (AnimationToPlay[1] != nullptr)
	{
		//UAnimSequence* AnimationToPlay = AnimationAsset.Object;
		// 애니메이션 재생
		goalHumanBody->PlayAnimation(AnimationToPlay[1], false);
		//goalHumanBody->SetPlayRate(animPlayTime); 
	}
	else
		return;
}

void UAnimLibrary::OnClicksitOnChair()
{
	selectedAnim = 2;
	
	if (AnimationToPlay[2] != nullptr)
	{
		// 애니메이션 재생
		goalHumanBody->PlayAnimation(AnimationToPlay[2], false);
	}
	else
		return;
}

void UAnimLibrary::OnClickstandingTalk()
{
	selectedAnim = 3;
	if (AnimationToPlay[3] != nullptr)
	{
		//UAnimSequence* AnimationToPlay = AnimationAsset.Object;
		
		// 애니메이션 재생
		goalHumanBody->PlayAnimation(AnimationToPlay[3], false);
	}
	else
		return;
}

void UAnimLibrary::OnClickstandingClap()
{
	selectedAnim = 4;
	
	if (AnimationToPlay[4] != nullptr)
	{
		//UAnimSequence* AnimationToPlay = AnimationAsset.Object;

		// 애니메이션 재생
		goalHumanBody->PlayAnimation(AnimationToPlay[4], false);
	}
	else
		return;
}

void UAnimLibrary::OnClickidle()
{
	selectedAnim = 5;
	
	if (AnimationToPlay[5] != nullptr)
	{
		//UAnimSequence* AnimationToPlay = AnimationAsset.Object;

		// 애니메이션 재생
		goalHumanBody->PlayAnimation(AnimationToPlay[5], false);
	}
	else
		return;
}

void UAnimLibrary::OnClickwalking()
{
	selectedAnim = 6;
	
	if (AnimationToPlay[6] != nullptr)
	{
		//UAnimSequence* AnimationToPlay = AnimationAsset.Object;

		// 애니메이션 재생
		goalHumanBody->PlayAnimation(AnimationToPlay[6], false);
	}
	else
		return;
}

void UAnimLibrary::OnClickback()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}

