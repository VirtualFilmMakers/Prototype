// Fill out your copyright notice in the Description page of Project Settings.


#include "MarkEditor.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "AnimLibrary.h"
#include "Components/Slider.h"
#include "MHActorA.h"
#include "SpawnActor.h"
#include "OSY_TESTCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/NoExportTypes.h"
#include "Kismet/KismetMathLibrary.h"



void UMarkEditor::NativeConstruct()
{
	Super::NativeConstruct(); //MarkEditor�� ���ܾ� ����Ǵ� �Լ�

	/*-------- Button Bind!! -------*/
	//UE_LOG(LogTemp,Warning,TEXT("MarkEditor perfect!"));
	World = GetWorld();
	btn_animSelection->OnClicked.AddDynamic(this, &UMarkEditor::OnClickAnimLib);
	slider_holdTime->OnValueChanged.AddDynamic(this, &UMarkEditor::OnSliderMoved);
	btn_addMark->OnClicked.AddDynamic(this, &UMarkEditor::OnClickAddMark);
	btn_after->OnClicked.AddDynamic(this, &UMarkEditor::OnClickAfterMark);
	btn_before->OnClicked.AddDynamic(this, &UMarkEditor::OnClickBeforeMark);
	btn_markStart->OnClicked.AddDynamic(this, &UMarkEditor::OnClickEntirePlay);


	//Player Controller
	pc = GetWorld()->GetFirstPlayerController();
	
	//Cast to OSY_TESTChararcter	
	player = Cast<AOSY_TESTCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AOSY_TESTCharacter::StaticClass()));
	
	//AnimSavedArray == Mark Anim Save array
	AnimSavedArray.Empty(100); //anim saved array size 100 set.

	for (int i = 0; i < 100; i++)
	{
		FAnimSavedStruct NewStruct;
		AnimSavedArray.Add(NewStruct);
	}
	
	//AnimLibWidget Created in MarkEditor Contructor.
	AnimLibWidget = CreateWidget<UAnimLibrary>(World, AnimLibClass); 
}


void UMarkEditor::SetCurrActor(AMHActorA* temp)
{
	CurrActor = temp;
	CurrActorSkeletal = CurrActor->FindComponentByClass<USkeletalMeshComponent>();

}

//btn_animSelection->OnClicked.AddDynamic(this, &UMarkEditor::OnClickAnimLib); //��ư�� ���õǸ� OnClickAnimLib() ����
	


void UMarkEditor::OnClickAnimLib()//Mark Editor����  Anim lib ��ư�� �����ϸ�
{
	//Anim lib UI�� ���� �ʹ�.
	/*if(!World) return;*/
	if (isCreated == false) {

		if (AnimLibWidget != nullptr)
		{
			AnimLibWidget->AddToViewport();
			pc->SetInputMode(FInputModeGameAndUI());
		}
		//AnimLibWidget->SetVisibility(ESlateVisibility::Visible);
		//enum CurAnimState currAnimState;
		isCreated = true;
	}
	else
	{
		AnimLibWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

//ADD MARK
void UMarkEditor::OnClickAddMark()
{
/*�ش� Mark�� ���� animation�� 
��ġ, ������ �����ؾ��ϴ� �κ�
*/
/*UE_LOG(LogTemp, Warning, TEXT("add mark"));*/
	isAdd = true;
	if (SpawnActor)
		GetWorld()->SpawnActor<ASpawnActor>(SpawnActor, CurrActor->GetActorLocation(), CurrActor->GetActorRotation()); //���� ĳ���� ����(���ο�Mark�� ���� ���� �ڸ��� ��Ű�� ĳ����)
	/*player->SetActorLocation(player->AddMarkLocation);*/

	//�÷��̾��� ���콺 ��Ŭ���� �޴´�. why? mark�� ���� ��ġ���� �ʿ��ϱ� ����

	//��Ŭ���� �ϸ� mark��ġ�� �ش� ��ġ�� �Űܰ���.

	FAnimSavedStruct newStruct;
	newStruct.ActorLocation = CurrActor->GetActorLocation();
	newStruct.ActorRotation = CurrActor->GetActorRotation();
	newStruct.Animindex = InputAnimState;
	newStruct.playTime = SliderPlayTime;

	if (MarkNumber >= 0 && MarkNumber < AnimSavedArray.Num())
	{
		FAnimSavedStruct& AccessedStruct = AnimSavedArray[MarkNumber];

		AccessedStruct.ActorLocation = newStruct.ActorLocation;
		AccessedStruct.ActorRotation = newStruct.ActorRotation;
		AccessedStruct.Animindex = newStruct.Animindex;
		AccessedStruct.playTime = newStruct.playTime;
	}
	else
	{
		if (MarkNumber < AnimSavedArray.Num())
		{
			AnimSavedArray.Add(newStruct);
			// 						UE_LOG(LogTemp, Warning, TEXT("%d"), AnimSavedArray[MarkNumber].Animindex);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AnimSave array Index error"));
			return;
		}

	}
	MarkNumber += 1;
	CurrMark = MarkNumber;
	
}

//MARK Editor's Anim player Time Slider
void UMarkEditor::OnSliderMoved(float value)
{
	text_sliderCount->SetText(FText::AsNumber((float)value));
	SliderPlayTime = value;
	
}


//������ ����
void UMarkEditor::OnClickAfterMark()
{
	// ���� ��ȸ�ϰ� �ִ� Mark�� ���� Mark�� ��ȸ�ϰ� �ʹ�.
	if(CurrMark+1>MarkNumber)
	{ 
		UE_LOG(LogTemp,Warning,TEXT("After Button Error = CurrPointer : %d, Total Mark Num : %d, ThisMarkAnim : %d "),CurrMark,MarkNumber,AnimSavedArray[CurrMark].Animindex);
		
	}
	else
	//1�� ������ ����Ѵٸ�..
	{
		CurrMark += 1;
		UE_LOG(LogTemp, Warning, TEXT("After Button Success!! = CurrPointer : %d, Total Mark Num : %d, ThisMarkAnim : %d, Location : x= %f, y=%f, Z=%f"), CurrMark, MarkNumber, AnimSavedArray[CurrMark].Animindex,AnimSavedArray[CurrMark].ActorLocation.X, AnimSavedArray[CurrMark].ActorLocation.Y, AnimSavedArray[CurrMark].ActorLocation.Z);
		CurrActor->SetActorLocation(AnimSavedArray[CurrMark].ActorLocation);
		CurrActorSkeletal->PlayAnimation(AnimLibWidget->GetAnimSequence(AnimSavedArray[CurrMark].Animindex), false);
		
		/*UE_LOG(LogTemp, Warning, TEXT("%f"), AnimLibWidget->GetAnimSequence(CurrMark)->GetPlayLength());*/
	}
}


//�ڷΰ���
void UMarkEditor::OnClickBeforeMark()
{
	// ���� ��ȸ�ϰ� �ִ� Mark�� ���� Mark�� ��ȸ�ϰ� �ʹ�.
	if (CurrMark-1 < 0)
	{
//1. ��ȸ�ϰ� �մ� Mark index�� 0���� �۾������� �ȵȴ�.
		UE_LOG(LogTemp, Warning, TEXT("Before Button Error = CurrPointer : %d, Total Mark Num : %d,ThisMarkAnim : %d"), CurrMark, MarkNumber, AnimSavedArray[CurrMark].Animindex);
	}
	//1�������� ����Ѵٸ�....
	else
	{
		CurrMark -= 1;
		UE_LOG(LogTemp, Warning, TEXT("Before Button Success!! = CurrPointer : %d, Total Mark Num : %d,ThisMarkAnim : %d ,Location : x= %f, y=%f, Z=%f"), CurrMark, MarkNumber, AnimSavedArray[CurrMark].Animindex, AnimSavedArray[CurrMark].ActorLocation.X, AnimSavedArray[CurrMark].ActorLocation.Y, AnimSavedArray[CurrMark].ActorLocation.Z);
		CurrActor->SetActorLocation(AnimSavedArray[CurrMark].ActorLocation);
		CurrActorSkeletal->PlayAnimation(AnimLibWidget->GetAnimSequence(AnimSavedArray[CurrMark].Animindex), false);
		/*UE_LOG(LogTemp, Warning, TEXT("%f"),AnimLibWidget->GetAnimSequence(AnimSavedArray[CurrMark].Animindex)->GetPlayLength());*/
	}

}


//��ü �÷ο�
void UMarkEditor::OnClickEntirePlay()
{
	CurrActor->SetActorLocation(AnimSavedArray[0].ActorLocation);
	CurrMark = 0;
	EntireMode = true;
		
}
	
//Rotation
float UMarkEditor::CalculateRotationDifference(FRotator CurrRot, FRotator TargetRot)
{
	FQuat CurrentQuat = CurrRot.Quaternion();
	FQuat TargetQuat = TargetRot.Quaternion();
	float AngleDifference = FMath::RadiansToDegrees(FMath::Acos(FMath::Clamp(CurrentQuat | TargetQuat, -1.f, 1.f))) * 2.f;
	return AngleDifference;
}

void UMarkEditor::RotateActorToDirection(FVector TargetDir, float RotSpeed)
{
	FVector CurrentForward = CurrActor->GetActorForwardVector();
	FRotator CurrentRotation = CurrActor->GetActorRotation();
	FRotator TargetRotation = UKismetMathLibrary::MakeRotFromX(TargetDir);

	// 
	float AngleDifference = CalculateRotationDifference(CurrentRotation, TargetRotation);

	// 
	FRotator NewRotation = UKismetMathLibrary::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), RotSpeed);
	CurrActor->SetActorRotation(NewRotation);
}


// void UMarkEditor::ME_MouseRight(void)
// {
// 	UE_LOG(LogTemp,Warning,TEXT("Practice?? REALLY??"));
// }

//TICK -> Animation Selection Input �޾ƿͼ� text ����
//TICK -> Animation Selection Input �޾ƿͼ� text ����
void UMarkEditor::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	//Super::NativeTick(MyGeometry, InDeltaTime);
	if (AnimLibWidget != nullptr)
		InputAnimState = AnimLibWidget->GetAnimInfo();

	if (EntireMode)
	{
		if (DistanceToTarget > 10 && !isArrive)
		{
			//UE_LOG(LogTemp, Warning, TEXT("gogo Entire!"));
			FVector P0 = CurrActor->GetActorLocation();
			FVector VT = 200 * dir * InDeltaTime;
			FVector P = P0 + VT;
			CurrActor->SetActorLocation(P);
			DistanceToTarget = FVector::Distance(CurrActor->GetActorLocation(), AnimSavedArray[CurrMark + 1].ActorLocation);
			UE_LOG(LogTemp, Warning, TEXT("dist : %f"), DistanceToTarget);
			if (currTime == 0)
				CurrActorSkeletal->PlayAnimation(WalkAnim, false);

			if (currTime > WalkAnim->GetPlayLength())
			{
				/*UE_LOG(LogTemp,Warning,TEXT("move Time!"));*/
				currTime = 0.0f;
			}
			else
			{
				currTime += InDeltaTime;

			}
		}
		else
		{
			isArrive = true;
			UE_LOG(LogTemp, Warning, TEXT("Mark# %d Access spot success!"), CurrMark);
			if (delTime == 0)
				CurrActorSkeletal->PlayAnimation(AnimLibWidget->GetAnimSequence(AnimSavedArray[CurrMark].Animindex), false);
			if (delTime < AnimSavedArray[CurrMark].playTime)
			{
				delTime += InDeltaTime;
			}
			else
			{

			}

			if (DistanceToTarget > 0)
			{
				UE_LOG(LogTemp, Warning, TEXT("CurrMark update!"));
				if (CurrMark + 1 < MarkNumber)
				{
					CurrMark += 1;
				}
				else EntireMode = false;
			}

			if (CurrMark + 1 < MarkNumber)
			{
				UE_LOG(LogTemp, Warning, TEXT("dir Update!"));
				dir = AnimSavedArray[CurrMark + 1].ActorLocation - AnimSavedArray[CurrMark].ActorLocation;
				dir.Normalize();
				CurrActor->SetActorRotation(dir.Rotation());

				DistanceToTarget = FVector::Distance(CurrActor->GetActorLocation(), AnimSavedArray[CurrMark + 1].ActorLocation);

				isArrive = false;
			}
		}
		//CurrActor->SetActorLocation(player->AddMarkLocation);

		// 				CurrActorSkeletal->PlayAnimation(AnimLibWidget->GetAnimSequence(AnimSavedArray[0].Animindex), false);
		// 				UE_LOG(LogTemp, Warning, TEXT("playTime = %f"), AnimSavedArray[0].playTime);
		// 		
		// 				for (int i = 0; i < MarkNumber-1; i++)
		// 				{
		// 				//spotA ,P0
		// 					FVector spotA = AnimSavedArray[i].ActorLocation;
		// 				//spotB
		// 					FVector spotB = AnimSavedArray[i+1].ActorLocation;
		// 		
		// 				//A to B distance
		// 				DistanceToTarget = FVector::Distance(spotA, spotB);
		// 				
		// 				
		// 				/*UE_LOG(LogTemp,Warning,TEXT("#%d : dist = %f"),i,DistanceToTarget);*/
		// 				
		// 				dir = spotB-spotA;
		// 				dir.Normalize();
		// 				currTime = 0;
		// 					while (DistanceToTarget > 10) 
		// 					{
		// 						
		// 						if (currTime < 1)
		// 						{
		// 							spotA = CurrActor->GetActorLocation();
		// 							FVector VT = dir * 100 * InDeltaTime;
		// 							FVector P = spotA + VT;
		// 							CurrActor->SetActorLocation(P);
		// 							DistanceToTarget = FVector::Distance(spotA, spotB);
		// 						}
		// 						else
		// 						{
		// 							currTime = 0;
		// 						}
		// 					}
		// 				}
		// 				EntireMode = false;
		// 				
	}

	switch (InputAnimState)
	{
	case 1:
		/*FButtonStyle ButtonStyle = btn_animSelection->WidgetStyle;*/
	{
		text_animName->SetText(FText::FromString("Sit On Ground"));
		//�� ����ü ��� ����
		FAnimSavedStruct newStruct;
		newStruct.ActorLocation = CurrActor->GetActorLocation();
		newStruct.ActorRotation = CurrActor->GetActorRotation();
		newStruct.Animindex = 1;

		// �ε����� ��ȿ�� ���� ���� �ִ��� Ȯ��
		if (MarkNumber >= 0 && MarkNumber < AnimSavedArray.Num())
		{
			// 				UE_LOG(LogTemp,Warning,TEXT("correct index"));


							// �ش� �ε����� ����ü ��Ҹ� ����
			FAnimSavedStruct& AccessedStruct = AnimSavedArray[MarkNumber];

			// �ش� �ε����� ����ü ��ҿ� ���� �Ҵ�
			AccessedStruct.ActorLocation = newStruct.ActorLocation;
			AccessedStruct.ActorRotation = newStruct.ActorRotation;
			AccessedStruct.Animindex = newStruct.Animindex;
			/*	UE_LOG(LogTemp, Warning, TEXT("Mark# %d : %d"), MarkNumber, AnimSavedArray[MarkNumber].Animindex);*/
		}
		else //�ε����� ��ȿ���� �ʴٸ�...
		{
			if (MarkNumber < AnimSavedArray.Num())
			{
				AnimSavedArray.Add(newStruct);
				UE_LOG(LogTemp, Warning, TEXT("%d"), AnimSavedArray[MarkNumber].Animindex);
			}
			else
				UE_LOG(LogTemp, Warning, TEXT("index error!!"));
		}

		break;
	}
	case 2:
	{
		text_animName->SetText(FText::FromString("Sit On Chair"));
		FAnimSavedStruct newStruct;
		newStruct.ActorLocation = CurrActor->GetActorLocation();
		newStruct.ActorRotation = CurrActor->GetActorRotation();
		newStruct.Animindex = 2;

		// �ε����� ��ȿ�� ���� ���� �ִ��� Ȯ��
		if (MarkNumber >= 0 && MarkNumber < AnimSavedArray.Num())
		{
			// 				UE_LOG(LogTemp, Warning, TEXT("correct index"));


							// �ش� �ε����� ����ü ��Ҹ� ����
			FAnimSavedStruct& AccessedStruct = AnimSavedArray[MarkNumber];

			// �ش� �ε����� ����ü ��ҿ� ���� �Ҵ�
			AccessedStruct.ActorLocation = newStruct.ActorLocation;
			AccessedStruct.ActorRotation = newStruct.ActorRotation;
			AccessedStruct.Animindex = newStruct.Animindex;
			/*UE_LOG(LogTemp, Warning, TEXT("Mark# %d : %d"),MarkNumber, AnimSavedArray[MarkNumber].Animindex);*/
		}
		else//�ε����� ��ȿ���� �ʴٸ�...
		{
			if (MarkNumber < AnimSavedArray.Num())
			{
				AnimSavedArray.Add(newStruct);
				UE_LOG(LogTemp, Warning, TEXT("%d"), AnimSavedArray[MarkNumber].Animindex);
			}
			else
				UE_LOG(LogTemp, Warning, TEXT("index error!!"));
		}
		break;
	}

	case 3:
	{
		text_animName->SetText(FText::FromString("Standing Talk"));

		FAnimSavedStruct newStruct;
		newStruct.ActorLocation = CurrActor->GetActorLocation();
		newStruct.ActorRotation = CurrActor->GetActorRotation();
		newStruct.Animindex = 3;

		// �ε����� ��ȿ�� ���� ���� �ִ��� Ȯ��
		if (MarkNumber >= 0 && MarkNumber < AnimSavedArray.Num())
		{
			/*UE_LOG(LogTemp, Warning, TEXT("correct index"));*/


			// �ش� �ε����� ����ü ��Ҹ� ����
			FAnimSavedStruct& AccessedStruct = AnimSavedArray[MarkNumber];

			// �ش� �ε����� ����ü ��ҿ� ���� �Ҵ�
			AccessedStruct.ActorLocation = newStruct.ActorLocation;
			AccessedStruct.ActorRotation = newStruct.ActorRotation;
			AccessedStruct.Animindex = newStruct.Animindex;
			/*	UE_LOG(LogTemp, Warning, TEXT("Mark# %d : %d"), MarkNumber, AnimSavedArray[MarkNumber].Animindex);*/
		}
		else//�ε����� ��ȿ���� �ʴٸ�...
		{
			if (MarkNumber < AnimSavedArray.Num())
			{
				AnimSavedArray.Add(newStruct);
				UE_LOG(LogTemp, Warning, TEXT("%d"), AnimSavedArray[MarkNumber].Animindex);
			}
			else
				UE_LOG(LogTemp, Warning, TEXT("index error!!"));
		}
		break;
	}

	case 4:
	{
		text_animName->SetText(FText::FromString("Standing Clap"));

		FAnimSavedStruct newStruct;
		newStruct.ActorLocation = CurrActor->GetActorLocation();
		newStruct.ActorRotation = CurrActor->GetActorRotation();
		newStruct.Animindex = 4;

		// �ε����� ��ȿ�� ���� ���� �ִ��� Ȯ��
		if (MarkNumber >= 0 && MarkNumber < AnimSavedArray.Num())
		{
			// 				UE_LOG(LogTemp, Warning, TEXT("correct index"));


							// �ش� �ε����� ����ü ��Ҹ� ����
			FAnimSavedStruct& AccessedStruct = AnimSavedArray[MarkNumber];

			// �ش� �ε����� ����ü ��ҿ� ���� �Ҵ�
			AccessedStruct.ActorLocation = newStruct.ActorLocation;
			AccessedStruct.ActorRotation = newStruct.ActorRotation;
			AccessedStruct.Animindex = newStruct.Animindex;
			/*UE_LOG(LogTemp, Warning, TEXT("Mark# %d : %d"), MarkNumber, AnimSavedArray[MarkNumber].Animindex);*/
		}
		else//�ε����� ��ȿ���� �ʴٸ�...
		{
			if (MarkNumber < AnimSavedArray.Num())
			{
				AnimSavedArray.Add(newStruct);
				UE_LOG(LogTemp, Warning, TEXT("%d"), AnimSavedArray[MarkNumber].Animindex);
			}
			else
				UE_LOG(LogTemp, Warning, TEXT("index error!!"));
		}
		break;
	}

	case 5:
	{
		text_animName->SetText(FText::FromString("Idle"));

		FAnimSavedStruct newStruct;
		newStruct.ActorLocation = CurrActor->GetActorLocation();
		newStruct.ActorRotation = CurrActor->GetActorRotation();
		newStruct.Animindex = 5;

		// �ε����� ��ȿ�� ���� ���� �ִ��� Ȯ��
		if (MarkNumber >= 0 && MarkNumber < AnimSavedArray.Num())
		{
			// 				UE_LOG(LogTemp, Warning, TEXT("correct index"));


							// �ش� �ε����� ����ü ��Ҹ� ����
			FAnimSavedStruct& AccessedStruct = AnimSavedArray[MarkNumber];

			// �ش� �ε����� ����ü ��ҿ� ���� �Ҵ�
			AccessedStruct.ActorLocation = newStruct.ActorLocation;
			AccessedStruct.ActorRotation = newStruct.ActorRotation;
			AccessedStruct.Animindex = newStruct.Animindex;
			/*	UE_LOG(LogTemp, Warning, TEXT("Mark# %d : %d"), MarkNumber, AnimSavedArray[MarkNumber].Animindex);*/
		}
		else//�ε����� ��ȿ���� �ʴٸ�...
		{
			if (MarkNumber < AnimSavedArray.Num())
			{
				AnimSavedArray.Add(newStruct);
				UE_LOG(LogTemp, Warning, TEXT("%d"), AnimSavedArray[MarkNumber].Animindex);
			}
			else
				UE_LOG(LogTemp, Warning, TEXT("index error!!"));
		}

		break;
	}

	case 6:
	{
		text_animName->SetText(FText::FromString("Walk"));

		FAnimSavedStruct newStruct;
		newStruct.ActorLocation = CurrActor->GetActorLocation();
		newStruct.ActorRotation = CurrActor->GetActorRotation();
		newStruct.Animindex = 6;

		// �ε����� ��ȿ�� ���� ���� �ִ��� Ȯ��
		if (MarkNumber >= 0 && MarkNumber < AnimSavedArray.Num())
		{
			// 				UE_LOG(LogTemp, Warning, TEXT("correct index"));


							// �ش� �ε����� ����ü ��Ҹ� ����
			FAnimSavedStruct& AccessedStruct = AnimSavedArray[MarkNumber];

			// �ش� �ε����� ����ü ��ҿ� ���� �Ҵ�
			AccessedStruct.ActorLocation = newStruct.ActorLocation;
			AccessedStruct.ActorRotation = newStruct.ActorRotation;
			AccessedStruct.Animindex = newStruct.Animindex;
			/*UE_LOG(LogTemp, Warning, TEXT("Mark# %d : %d"), MarkNumber, AnimSavedArray[MarkNumber].Animindex);*/
		}
		else//�ε����� ��ȿ���� �ʴٸ�...
		{
			if (MarkNumber < AnimSavedArray.Num())
			{
				AnimSavedArray.Add(newStruct);
				UE_LOG(LogTemp, Warning, TEXT("%d"), AnimSavedArray[MarkNumber].Animindex);
			}
			else
				UE_LOG(LogTemp, Warning, TEXT("index error!!"));
		}

		break;
	}

	default:
	{
		text_animName->SetText(FText::FromString("Idle"));

		FAnimSavedStruct newStruct;
		newStruct.ActorLocation = CurrActor->GetActorLocation();
		newStruct.ActorRotation = CurrActor->GetActorRotation();
		newStruct.Animindex = 5;

		// �ε����� ��ȿ�� ���� ���� �ִ��� Ȯ��
		if (MarkNumber >= 0 && MarkNumber < AnimSavedArray.Num())
		{
			// 				UE_LOG(LogTemp, Warning, TEXT("correct index"));


							// �ش� �ε����� ����ü ��Ҹ� ����
			FAnimSavedStruct& AccessedStruct = AnimSavedArray[MarkNumber];

			// �ش� �ε����� ����ü ��ҿ� ���� �Ҵ�
			AccessedStruct.ActorLocation = newStruct.ActorLocation;
			AccessedStruct.ActorRotation = newStruct.ActorRotation;
			AccessedStruct.Animindex = newStruct.Animindex;
			/*	UE_LOG(LogTemp, Warning, TEXT("Mark# %d : %d"), MarkNumber, AnimSavedArray[MarkNumber].Animindex);*/
		}
		else//�ε����� ��ȿ���� �ʴٸ�...
		{
			if (MarkNumber < AnimSavedArray.Num())
			{
				AnimSavedArray.Add(newStruct);
				UE_LOG(LogTemp, Warning, TEXT("%d"), AnimSavedArray[MarkNumber].Animindex);
			}
			else
				UE_LOG(LogTemp, Warning, TEXT("index error!!"));
		}

		break;

	}
	}
}
