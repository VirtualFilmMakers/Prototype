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
	//����� ��ġ�� ��Ÿ�޸��� ����(acoter��)�� �����´�.
	//1. ���� �� ��ġ�� ��� ���� ������ �迭�� �޾ƿ´�.
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
	
	// 	//���� ��ư�� �ش��ϴ� MarkEditor �̹����� �ؽ�Ʈ�� ������Ʈ�Ѵ�.
 	selectedAnim = 1;
	//UAnimInstance* ai = goalHumanBody->GetAnimInstance();
	AnimationToPlay = nullptr;
	AnimationToPlay = Cast<UAnimSequence>(
		StaticLoadObject(UAnimSequence::StaticClass(), NULL, TEXT("/Script/Engine.AnimSequence'/Game/LHJ/Anim/MetaHuman/MH_MA_Sitting_Idle_Anim.MH_MA_Sitting_Idle_Anim'")));
	if (AnimationToPlay != nullptr)
	{
		//UAnimSequence* AnimationToPlay = AnimationAsset.Object;
	

		// �ִϸ��̼� ���
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
		
		// �ִϸ��̼� ���
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
		
		// �ִϸ��̼� ���
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

		// �ִϸ��̼� ���
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

		// �ִϸ��̼� ���
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

		// �ִϸ��̼� ���
		goalHumanBody->PlayAnimation(AnimationToPlay, false);
	}
	else
		return;
}

void UAnimLibrary::OnClickback()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}

