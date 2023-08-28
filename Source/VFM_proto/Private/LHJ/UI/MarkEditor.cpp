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
	Super::NativeConstruct(); //MarkEditor가 생겨야 실행되는 함수

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

//btn_animSelection->OnClicked.AddDynamic(this, &UMarkEditor::OnClickAnimLib); //버튼이 선택되면 OnClickAnimLib() 실행
	


void UMarkEditor::OnClickAnimLib()//Mark Editor에서  Anim lib 버튼을 선택하면
{
	//Anim lib UI를 띄우고 싶다.
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
/*해당 Mark의 현재 animation과 
위치, 방향을 저장해야하는 부분
*/
/*UE_LOG(LogTemp, Warning, TEXT("add mark"));*/
// 	isAdd = true;
// 	SpawnActorHologramServer(); //가상 캐릭터 스폰(새로운Mark를 위해 본래 자리를 지키는 캐릭터)
	/*player->SetActorLocation(player->AddMarkLocation);*/
	isAdd = true;
	if (SpawnActor)
		GetWorld()->SpawnActor<ASpawnActor>(SpawnActor, CurrActor->GetActorLocation(), CurrActor->GetActorRotation());
	//플레이어의 마우스 우클릭을 받는다. why? mark를 찍을 위치값이 필요하기 때문

	//우클릭을 하면 mark위치가 해당 위치로 옮겨간다.

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


//앞으로 가기
void UMarkEditor::OnClickAfterMark()
{
	// 현재 조회하고 있는 Mark의 다음 Mark를 조회하고 싶다.
	if(CurrMark+1>MarkNumber)
	{ 
		UE_LOG(LogTemp,Warning,TEXT("After Button Error = CurrPointer : %d, Total Mark Num : %d, ThisMarkAnim : %d "),CurrMark,MarkNumber,AnimSavedArray[CurrMark].Animindex);
		
	}
	else
	//1번 조건을 통과한다면..
	{
		CurrMark += 1;
		UE_LOG(LogTemp, Warning, TEXT("After Button Success!! = CurrPointer : %d, Total Mark Num : %d, ThisMarkAnim : %d, Location : x= %f, y=%f, Z=%f"), CurrMark, MarkNumber, AnimSavedArray[CurrMark].Animindex,AnimSavedArray[CurrMark].ActorLocation.X, AnimSavedArray[CurrMark].ActorLocation.Y, AnimSavedArray[CurrMark].ActorLocation.Z);
		CurrActor->SetActorLocation(AnimSavedArray[CurrMark].ActorLocation);
		CurrActor->IndexPlayAnim(AnimSavedArray[CurrMark].Animindex);
		/*CurrActorSkeletal->PlayAnimation(AnimLibWidget->GetAnimSequence(AnimSavedArray[CurrMark].Animindex), false);*/
		
		/*UE_LOG(LogTemp, Warning, TEXT("%f"), AnimLibWidget->GetAnimSequence(CurrMark)->GetPlayLength());*/
	}
}


//뒤로가기
void UMarkEditor::OnClickBeforeMark()
{
	// 현재 조회하고 있는 Mark의 이전 Mark를 조회하고 싶다.
	if (CurrMark-1 < 0)
	{
//1. 조회하고 잇는 Mark index가 0보다 작아져서는 안된다.
		UE_LOG(LogTemp, Warning, TEXT("Before Button Error = CurrPointer : %d, Total Mark Num : %d,ThisMarkAnim : %d"), CurrMark, MarkNumber, AnimSavedArray[CurrMark].Animindex);
	}
	//1번조건을 통과한다면....
	else
	{
		CurrMark -= 1;
		UE_LOG(LogTemp, Warning, TEXT("Before Button Success!! = CurrPointer : %d, Total Mark Num : %d,ThisMarkAnim : %d ,Location : x= %f, y=%f, Z=%f"), CurrMark, MarkNumber, AnimSavedArray[CurrMark].Animindex, AnimSavedArray[CurrMark].ActorLocation.X, AnimSavedArray[CurrMark].ActorLocation.Y, AnimSavedArray[CurrMark].ActorLocation.Z);
		CurrActor->SetActorLocation(AnimSavedArray[CurrMark].ActorLocation);
		CurrActor->IndexPlayAnim(AnimSavedArray[CurrMark].Animindex);
		/*CurrActorSkeletal->PlayAnimation(AnimLibWidget->GetAnimSequence(AnimSavedArray[CurrMark].Animindex), false);*/
		/*UE_LOG(LogTemp, Warning, TEXT("%f"),AnimLibWidget->GetAnimSequence(AnimSavedArray[CurrMark].Animindex)->GetPlayLength());*/
	}

}


//전체 플로우
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
	FRotator TargetRotation = UKismetMathLibrary::MakeRotFromXZ(TargetDir, CurrActor->GetActorUpVector());

	// 
	float AngleDifference = CalculateRotationDifference(CurrentRotation, TargetRotation);

	// 
	FRotator NewRotation = UKismetMathLibrary::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), RotSpeed);
	CurrActor->SetActorRotation(NewRotation);
}


void UMarkEditor::SpawnActorHologramServer_Implementation()
{
	SpawnActorHologramMulticast();
}

bool UMarkEditor::SpawnActorHologramServer_Validate()
{
	return true;
}

void UMarkEditor::SpawnActorHologramMulticast_Implementation()
{
	isAdd = true;
	if (SpawnActor)
		GetWorld()->SpawnActor<ASpawnActor>(SpawnActor, CurrActor->GetActorLocation(), CurrActor->GetActorRotation()); //가상 캐릭터 스폰(새로운Mark를 위해 본래 자리를 지키는 캐릭터)
}

// void UMarkEditor::ME_MouseRight(void)
// {
// 	UE_LOG(LogTemp,Warning,TEXT("Practice?? REALLY??"));
// }

//TICK -> Animation Selection Input 받아와서 text 변경
//TICK -> Animation Selection Input 받아와서 text 변경
void UMarkEditor::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	//Super::NativeTick(MyGeometry, InDeltaTime);
	if (AnimLibWidget != nullptr)
		InputAnimState = AnimLibWidget->GetAnimInfo();

	if (EntireMode) //Entire play btn pressed
	{
		if (DistanceToTarget > 10 && !isArrive && !playAnimMode) //IF, mark to mark distance remain 10 and not arrived and not playAnimMode..
		{
			//UE_LOG(LogTemp, Warning, TEXT("gogo Entire!"));
			FVector P0 = CurrActor->GetActorLocation();
			FVector VT = 200 * dir * InDeltaTime;
			FVector P = P0 + VT;
			
			//Move
			CurrActor->SetActorLocation(P); 
			//distance renew
			DistanceToTarget = FVector::Distance(CurrActor->GetActorLocation(), AnimSavedArray[CurrMark + 1].ActorLocation);
			UE_LOG(LogTemp, Warning, TEXT("dist : %f"), DistanceToTarget);
			
			/* Walking Anim Play */
			if (currTime == 0) //WalkingAnim Timer On
				CurrActor->StartWalkServer();
				//CurrActorSkeletal->PlayAnimation(WalkAnim, false);

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
		else // Mark Arrived
		{
			isArrive = true; // Mark Arrived
			playAnimMode = true; //Play Anim Mode On!
			UE_LOG(LogTemp, Warning, TEXT("Mark# %d Access spot success!"), CurrMark);
			
				/*CurrActorSkeletal->PlayAnimation(AnimLibWidget->GetAnimSequence(AnimSavedArray[CurrMark].Animindex), false);*/
			if (delTime < AnimSavedArray[CurrMark].playTime)
			{
				if (delTime == 0)
					CurrActor->IndexPlayAnim(AnimSavedArray[CurrMark].Animindex); 
				delTime += InDeltaTime;
			}
			else
			{
				delTime = 0;
				CurrActor->IndexStopAnim();
				playAnimMode = false;

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

			
		}
		
	}


	switch (InputAnimState)
	{
	case 1:
		/*FButtonStyle ButtonStyle = btn_animSelection->WidgetStyle;*/
	{
		text_animName->SetText(FText::FromString("Sit On Ground"));
		//새 구조체 요소 생성
		FAnimSavedStruct newStruct;
		newStruct.ActorLocation = CurrActor->GetActorLocation();
		newStruct.ActorRotation = CurrActor->GetActorRotation();
		newStruct.Animindex = 1;

		// 인덱스가 유효한 범위 내에 있는지 확인
		if (MarkNumber >= 0 && MarkNumber < AnimSavedArray.Num())
		{
			// 				UE_LOG(LogTemp,Warning,TEXT("correct index"));


							// 해당 인덱스의 구조체 요소를 참조
			FAnimSavedStruct& AccessedStruct = AnimSavedArray[MarkNumber];

			// 해당 인덱스의 구조체 요소에 값을 할당
			AccessedStruct.ActorLocation = newStruct.ActorLocation;
			AccessedStruct.ActorRotation = newStruct.ActorRotation;
			AccessedStruct.Animindex = newStruct.Animindex;
			/*	UE_LOG(LogTemp, Warning, TEXT("Mark# %d : %d"), MarkNumber, AnimSavedArray[MarkNumber].Animindex);*/
		}
		else //인덱스가 유효하지 않다면...
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

		// 인덱스가 유효한 범위 내에 있는지 확인
		if (MarkNumber >= 0 && MarkNumber < AnimSavedArray.Num())
		{
			// 				UE_LOG(LogTemp, Warning, TEXT("correct index"));


							// 해당 인덱스의 구조체 요소를 참조
			FAnimSavedStruct& AccessedStruct = AnimSavedArray[MarkNumber];

			// 해당 인덱스의 구조체 요소에 값을 할당
			AccessedStruct.ActorLocation = newStruct.ActorLocation;
			AccessedStruct.ActorRotation = newStruct.ActorRotation;
			AccessedStruct.Animindex = newStruct.Animindex;
			/*UE_LOG(LogTemp, Warning, TEXT("Mark# %d : %d"),MarkNumber, AnimSavedArray[MarkNumber].Animindex);*/
		}
		else//인덱스가 유효하지 않다면...
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

		// 인덱스가 유효한 범위 내에 있는지 확인
		if (MarkNumber >= 0 && MarkNumber < AnimSavedArray.Num())
		{
			/*UE_LOG(LogTemp, Warning, TEXT("correct index"));*/


			// 해당 인덱스의 구조체 요소를 참조
			FAnimSavedStruct& AccessedStruct = AnimSavedArray[MarkNumber];

			// 해당 인덱스의 구조체 요소에 값을 할당
			AccessedStruct.ActorLocation = newStruct.ActorLocation;
			AccessedStruct.ActorRotation = newStruct.ActorRotation;
			AccessedStruct.Animindex = newStruct.Animindex;
			/*	UE_LOG(LogTemp, Warning, TEXT("Mark# %d : %d"), MarkNumber, AnimSavedArray[MarkNumber].Animindex);*/
		}
		else//인덱스가 유효하지 않다면...
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

		// 인덱스가 유효한 범위 내에 있는지 확인
		if (MarkNumber >= 0 && MarkNumber < AnimSavedArray.Num())
		{
			// 				UE_LOG(LogTemp, Warning, TEXT("correct index"));


							// 해당 인덱스의 구조체 요소를 참조
			FAnimSavedStruct& AccessedStruct = AnimSavedArray[MarkNumber];

			// 해당 인덱스의 구조체 요소에 값을 할당
			AccessedStruct.ActorLocation = newStruct.ActorLocation;
			AccessedStruct.ActorRotation = newStruct.ActorRotation;
			AccessedStruct.Animindex = newStruct.Animindex;
			/*UE_LOG(LogTemp, Warning, TEXT("Mark# %d : %d"), MarkNumber, AnimSavedArray[MarkNumber].Animindex);*/
		}
		else//인덱스가 유효하지 않다면...
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

		// 인덱스가 유효한 범위 내에 있는지 확인
		if (MarkNumber >= 0 && MarkNumber < AnimSavedArray.Num())
		{
			// 				UE_LOG(LogTemp, Warning, TEXT("correct index"));


							// 해당 인덱스의 구조체 요소를 참조
			FAnimSavedStruct& AccessedStruct = AnimSavedArray[MarkNumber];

			// 해당 인덱스의 구조체 요소에 값을 할당
			AccessedStruct.ActorLocation = newStruct.ActorLocation;
			AccessedStruct.ActorRotation = newStruct.ActorRotation;
			AccessedStruct.Animindex = newStruct.Animindex;
			/*	UE_LOG(LogTemp, Warning, TEXT("Mark# %d : %d"), MarkNumber, AnimSavedArray[MarkNumber].Animindex);*/
		}
		else//인덱스가 유효하지 않다면...
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

		// 인덱스가 유효한 범위 내에 있는지 확인
		if (MarkNumber >= 0 && MarkNumber < AnimSavedArray.Num())
		{
			// 				UE_LOG(LogTemp, Warning, TEXT("correct index"));


							// 해당 인덱스의 구조체 요소를 참조
			FAnimSavedStruct& AccessedStruct = AnimSavedArray[MarkNumber];

			// 해당 인덱스의 구조체 요소에 값을 할당
			AccessedStruct.ActorLocation = newStruct.ActorLocation;
			AccessedStruct.ActorRotation = newStruct.ActorRotation;
			AccessedStruct.Animindex = newStruct.Animindex;
			/*UE_LOG(LogTemp, Warning, TEXT("Mark# %d : %d"), MarkNumber, AnimSavedArray[MarkNumber].Animindex);*/
		}
		else//인덱스가 유효하지 않다면...
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

		// 인덱스가 유효한 범위 내에 있는지 확인
		if (MarkNumber >= 0 && MarkNumber < AnimSavedArray.Num())
		{
			// 				UE_LOG(LogTemp, Warning, TEXT("correct index"));


							// 해당 인덱스의 구조체 요소를 참조
			FAnimSavedStruct& AccessedStruct = AnimSavedArray[MarkNumber];

			// 해당 인덱스의 구조체 요소에 값을 할당
			AccessedStruct.ActorLocation = newStruct.ActorLocation;
			AccessedStruct.ActorRotation = newStruct.ActorRotation;
			AccessedStruct.Animindex = newStruct.Animindex;
			/*	UE_LOG(LogTemp, Warning, TEXT("Mark# %d : %d"), MarkNumber, AnimSavedArray[MarkNumber].Animindex);*/
		}
		else//인덱스가 유효하지 않다면...
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
