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



	pc = GetWorld()->GetFirstPlayerController();
	
	player = Cast<AOSY_TESTCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AOSY_TESTCharacter::StaticClass()));
	AnimSavedArray.Empty(100); //anim saved array size 100 set.

	for (int i = 0; i < 100; i++)
	{
		FAnimSavedStruct NewStruct;
		AnimSavedArray.Add(NewStruct);
	}
	//if(pc) UE_LOG(LogTemp,Warning,TEXT("PC good job!!!!!!!!")); //�÷��̾� ��Ʈ�ѷ� �޾ƿ���
	//
	//
	/*AnimLibClass = UAnimLibrary::StaticClass();*///Ŭ���� ��ü(���赵) ��������
	//
	//MarkEditorWidget = CreateWidget<UMarkEditor>(pc,MarkEditorClass);
//	//������ ���赵�� ���� ����
//
//	//������ ������ ������ ����.
	////if (MarkEditorWidget) // mark editor�� ���������� ��������ٸ�
	////{
	////	MarkEditorWidget->AddToViewport();
	////} 
	
/*	player->InputComponent->BindAction*//*("PlaceMark",IE_Pressed,this,&UMarkEditor::ME_MouseRight);*/
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
	if(!World) return;

	if(isCreated==false){
	AnimLibWidget = CreateWidget<UAnimLibrary>(World,AnimLibClass);
	if (AnimLibWidget!=nullptr)
	{
		AnimLibWidget->AddToViewport();
		//pc->SetInputMode(FInputModeGameAndUI());
	}
	//enum CurAnimState currAnimState;
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
	MarkNumber+=1;
	CurrMark=MarkNumber;
	/*UE_LOG(LogTemp, Warning, TEXT("add mark"));*/
	if(SpawnActor)
	GetWorld()->SpawnActor<ASpawnActor>(SpawnActor, CurrActor->GetActorLocation(), CurrActor->GetActorRotation()); //���� ĳ���� ����(���ο�Mark�� ���� ���� �ڸ��� ��Ű�� ĳ����)
	/*player->SetActorLocation(player->AddMarkLocation);*/

	//�÷��̾��� ���콺 ��Ŭ���� �޴´�. why? mark�� ���� ��ġ���� �ʿ��ϱ� ����
	
	//��Ŭ���� �ϸ� mark��ġ�� �ش� ��ġ�� �Űܰ���.


	
}

//MARK Editor's Anim player Time Slider
void UMarkEditor::OnSliderMoved(float value)
{
	text_sliderCount->SetText(FText::AsNumber((float)value));
	
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
	EntireMode = true;
// 	currTime = 0;
// 	CurrActor->SetActorLocation(AnimSavedArray[0].ActorLocation);
// 	//���� ��ũ���� �ɾ�� �ʹ�.
// 	//���� ��ũ ��ġ
// 	FVector P0 ;
// 	FVector goal = AnimSavedArray[1].ActorLocation;
// 	FVector dir = goal - P0;
// 	//dir.Normalize();
// 	/*CurrActor->SetActorLocation(P0 + 100 * delTime * dir);*/
// 	
// 		//�ɾ�� �ʹ�.->�ִ��÷��� + �ӵ�&����
// 
// 	for (int i = 0; i < 100; i++)
// 	{
// 		if (TimeOut)
// 		{
// 			P0 = CurrActor->GetActorLocation();
// 			UE_LOG(LogTemp,Warning,TEXT("Move!"));
// 			CurrActor->SetActorLocation(P0+dir*50*delTime);
// 		}
// 		else
// 		{
// 			UE_LOG(LogTemp, Warning, TEXT("Not Move!"));
// 		}
// 	}
// 	for (int i = 0; i < 10; i++)
// 	{
// 		UE_LOG(LogTemp,Warning,TEXT("%f"),GetWorld()->GetDeltaSeconds()*100);
// 	}
//�ð��� ����.
// �ִ� Ÿ�Ӻ��� Ÿ�̸� �ð��� Ŀ���� ���� �ִ����� �ѱ�, Ÿ�̸� �ʱ�ȭ
// ��, �ִ� Ÿ���� ��ȸ�ϴ� idx �ִ� ���� �迭���̺��� �۾ƾ��� 
//�ƴ϶�� �ִ� �÷���
// 	for(int i=1; i<MarkNumber;i++)
// 	{ 
// 		FVector Target = AnimSavedArray[i].ActorLocation;
// 		FVector dir = Target - CurrActor->GetActorLocation(); //Ÿ�� - me
// 		FVector P0 = CurrActor->GetActorLocation();
// 		FVector VT = 500*GetWorld()->DeltaTimeSeconds*dir;
// 		FVector P = P0+VT;
// 		while (CurrActor->GetActorLocation() != Target)
// 		{
// 			CurrActor->SetActorLocation(P);
// 		}
// 		/*UE_LOG(LogTemp,Warning,TEXT("Anim# %d"),i+1);*/
// 
// 		
// 	}

// 		while (currTime < 100.0f) //�� �ִϸ��̼� �÷���Ÿ�� �����ͼ� Ÿ�̸�ó�� ���
// 		{
// 			currTime += GetWorld()->GetRealTimeSeconds();
// 			/*UE_LOG(LogTemp, Warning, TEXT("%f"), currTime);*/
// 		}
// 		currTime=0;
// 		UE_LOG(LogTemp, Warning, TEXT("Time out! #%d"), i);
	
//GetWorld()->DeltaTimeSeconds
// 	for(int i=0; i<MarkNumber;i++)
// 	{
// 		float AnimPlayTime = 0;
// 		AnimPlayTime = AnimLibWidget->GetAnimSequence(AnimSavedArray[i].Animindex)
// 		CurrActor->SetActorLocation(AnimSavedArray[i].ActorLocation);
// 		CurrActorSkeletal->PlayAnimation(AnimLibWidget->GetAnimSequence(AnimSavedArray[i].Animindex), false);

		
}
	


// void UMarkEditor::ME_MouseRight(void)
// {
// 	UE_LOG(LogTemp,Warning,TEXT("Practice?? REALLY??"));
// }

//TICK -> Animation Selection Input �޾ƿͼ� text ����
void UMarkEditor::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	//Super::NativeTick(MyGeometry, InDeltaTime);
	if(AnimLibWidget!=nullptr)
	InputAnimState = AnimLibWidget->GetAnimInfo();

	//���⼭ � ������ �־�����ұ�?
	//ray�� ���� �÷��̾� ��ġ�� player->AddMarkLocation���� �޾ƿ´�.
	// <- ->�� ���� �÷��̾� ��ġ�� ���̺��� �о�´�.
	//�װ��� ƽ���� �׻� ���� ���ش�.
	
	delTime = InDeltaTime;
	TimeOut = false;
// 	if (currTime >= 0.1)
// 	{
// 		UE_LOG(LogTemp,Warning,TEXT("Time out!!!"));
// 		currTime=0.0f;
// 		TimeOut = true;
// 	}
	if (EntireMode)
	{
		if(currTime==0)CurrActorSkeletal->PlayAnimation(WalkAnim, true);
		currTime+=InDeltaTime;
		CurrActor->SetActorLocation(CurrActor->GetActorLocation() + CurrActor->GetActorForwardVector() * delTime * 200);
		
		if (currTime > WalkAnim->GetPlayLength())
		{
			/*UE_LOG(LogTemp,Warning,TEXT("move Time!"));*/
			currTime = 0.0f;
		}
	}

	//CurrActor->SetActorLocation(player->AddMarkLocation);
	
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
			if (MarkNumber>= 0 && MarkNumber < AnimSavedArray.Num())
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
				if(MarkNumber < AnimSavedArray.Num())
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
