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



	pc = GetWorld()->GetFirstPlayerController();
	
	player = Cast<AOSY_TESTCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AOSY_TESTCharacter::StaticClass()));
	AnimSavedArray.Empty(100); //anim saved array size 100 set.

	for (int i = 0; i < 100; i++)
	{
		FAnimSavedStruct NewStruct;
		AnimSavedArray.Add(NewStruct);
	}
	//if(pc) UE_LOG(LogTemp,Warning,TEXT("PC good job!!!!!!!!")); //플레이어 컨트롤러 받아오기
	//
	//
	/*AnimLibClass = UAnimLibrary::StaticClass();*///클래스 객체(설계도) 가져오기
	//
	//MarkEditorWidget = CreateWidget<UMarkEditor>(pc,MarkEditorClass);
//	//가져온 설계도로 위젯 생성
//
//	//생성한 위젯을 레벨에 띄운다.
	////if (MarkEditorWidget) // mark editor가 성공적으로 만들어졌다면
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

//btn_animSelection->OnClicked.AddDynamic(this, &UMarkEditor::OnClickAnimLib); //버튼이 선택되면 OnClickAnimLib() 실행
	


void UMarkEditor::OnClickAnimLib()//Mark Editor에서  Anim lib 버튼을 선택하면
{
	//Anim lib UI를 띄우고 싶다.
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
/*해당 Mark의 현재 animation과 
위치, 방향을 저장해야하는 부분
*/
	MarkNumber+=1;
	CurrMark=MarkNumber;
	/*UE_LOG(LogTemp, Warning, TEXT("add mark"));*/
	if(SpawnActor)
	GetWorld()->SpawnActor<ASpawnActor>(SpawnActor, CurrActor->GetActorLocation(), CurrActor->GetActorRotation()); //가상 캐릭터 스폰(새로운Mark를 위해 본래 자리를 지키는 캐릭터)
	/*player->SetActorLocation(player->AddMarkLocation);*/

	//플레이어의 마우스 우클릭을 받는다. why? mark를 찍을 위치값이 필요하기 때문
	
	//우클릭을 하면 mark위치가 해당 위치로 옮겨간다.


	
}

//MARK Editor's Anim player Time Slider
void UMarkEditor::OnSliderMoved(float value)
{
	text_sliderCount->SetText(FText::AsNumber((float)value));
	
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
		CurrActorSkeletal->PlayAnimation(AnimLibWidget->GetAnimSequence(AnimSavedArray[CurrMark].Animindex), false);
		
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
		CurrActorSkeletal->PlayAnimation(AnimLibWidget->GetAnimSequence(AnimSavedArray[CurrMark].Animindex), false);
		/*UE_LOG(LogTemp, Warning, TEXT("%f"),AnimLibWidget->GetAnimSequence(AnimSavedArray[CurrMark].Animindex)->GetPlayLength());*/
	}

}


//전체 플로우
void UMarkEditor::OnClickEntirePlay()
{
	EntireMode = true;
// 	currTime = 0;
// 	CurrActor->SetActorLocation(AnimSavedArray[0].ActorLocation);
// 	//다음 마크까지 걸어가고 싶다.
// 	//다음 마크 위치
// 	FVector P0 ;
// 	FVector goal = AnimSavedArray[1].ActorLocation;
// 	FVector dir = goal - P0;
// 	//dir.Normalize();
// 	/*CurrActor->SetActorLocation(P0 + 100 * delTime * dir);*/
// 	
// 		//걸어가고 싶다.->애님플레이 + 속도&방향
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
//시간이 간다.
// 애님 타임보다 타이머 시간이 커지면 다음 애님으로 넘김, 타이머 초기화
// 단, 애님 타임을 조회하는 idx 애님 종류 배열길이보다 작아야함 
//아니라면 애님 플레이
// 	for(int i=1; i<MarkNumber;i++)
// 	{ 
// 		FVector Target = AnimSavedArray[i].ActorLocation;
// 		FVector dir = Target - CurrActor->GetActorLocation(); //타겟 - me
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

// 		while (currTime < 100.0f) //각 애니메이션 플레이타임 가져와서 타이머처럼 사용
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

//TICK -> Animation Selection Input 받아와서 text 변경
void UMarkEditor::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	//Super::NativeTick(MyGeometry, InDeltaTime);
	if(AnimLibWidget!=nullptr)
	InputAnimState = AnimLibWidget->GetAnimInfo();

	//여기서 어떤 조건을 넣어줘야할까?
	//ray로 인한 플레이어 위치는 player->AddMarkLocation에서 받아온다.
	// <- ->로 인한 플레이어 위치는 테이블에서 읽어온다.
	//그것을 틱으로 항상 조절 해준다.
	
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
			//새 구조체 요소 생성
			FAnimSavedStruct newStruct;
			newStruct.ActorLocation = CurrActor->GetActorLocation();
			newStruct.ActorRotation = CurrActor->GetActorRotation();
			newStruct.Animindex = 1;
		
			// 인덱스가 유효한 범위 내에 있는지 확인
			if (MarkNumber>= 0 && MarkNumber < AnimSavedArray.Num())
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
