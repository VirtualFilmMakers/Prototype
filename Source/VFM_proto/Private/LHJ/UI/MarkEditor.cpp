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
	

	//컨트롤러 받아옴
	pc = GetWorld()->GetFirstPlayerController();
	
	//플레이어 캐스트해옴
	player = Cast<AOSY_TESTCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AOSY_TESTCharacter::StaticClass()));
	
	//각 마크마다의 정보를 저장할 구조체 배열 만듦
	//비어있는 배열로 사이즈100으로 만들어옴. 
	AnimSavedArray.Empty(100); //anim saved array size 100 set.

	//구조체 배열에 구조체 넣어주기. 인덱스 오류 방지용으로 인덱스는 idle을 가르키는 5로 채워넣어줌
	for (int i = 0; i < 100; i++)
	{
		FAnimSavedStruct NewStruct;
		NewStruct.Animindex = 5;
		AnimSavedArray.Add(NewStruct);
	}
	// AnimLibrary 위젯을 만들어 놓는다.
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
/*	if (!World) return;*/

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
*/	isAdd=true;
	
	/*UE_LOG(LogTemp, Warning, TEXT("add mark"));*/
	if(SpawnActor)
	GetWorld()->SpawnActor<ASpawnActor>(SpawnActor, CurrActor->GetActorLocation(), CurrActor->GetActorRotation()); //가상 캐릭터 스폰(새로운Mark를 위해 본래 자리를 지키는 캐릭터)
	/*player->SetActorLocation(player->AddMarkLocation);*/

	//플레이어의 마우스 우클릭을 받는다. why? mark를 찍을 위치값이 필요하기 때문
	
	//우클릭을 하면 mark위치가 해당 위치로 옮겨간다.

	//
	FAnimSavedStruct newStruct;
	newStruct.ActorLocation = CurrActor->GetActorLocation();
	newStruct.ActorRotation = CurrActor->GetActorRotation();
	newStruct.Animindex = InputAnimState;
	newStruct.playTime = SliderPlayTime;
	
	// 인덱스가 유효한 범위 내에 있는지 확인
	if (MarkNumber>= 0 && MarkNumber < AnimSavedArray.Num())
	{
		FAnimSavedStruct& AccessedStruct = AnimSavedArray[MarkNumber];
		// 해당 인덱스의 구조체 요소에 값을 할당
		AccessedStruct.ActorLocation = newStruct.ActorLocation;
		AccessedStruct.ActorRotation = newStruct.ActorRotation;
		AccessedStruct.Animindex = newStruct.Animindex;
		AccessedStruct.playTime = newStruct.playTime;
	}
	else //인덱스가 범위 밖에 있을때
	{
		if (MarkNumber < AnimSavedArray.Num()) 	
		{ 
			AnimSavedArray.Add(newStruct);
				// 						UE_LOG(LogTemp, Warning, TEXT("%d"), AnimSavedArray[MarkNumber].Animindex);
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("AnimSave array Index error"));
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


//전체 플로우 재생
void UMarkEditor::OnClickEntirePlay()
{
	
	//맨처음 Mark로 순간이동
	CurrActor->SetActorLocation(AnimSavedArray[0].ActorLocation);
	CurrMark = 0;
	EntireMode = true;

// 	while (currTime < AnimSavedArray[0].playTime)
// 	{
// 		currTime+=GetWorld()->DeltaRealTimeSeconds;
// 		UE_LOG(LogTemp, Warning, TEXT("playtime = %f, CurrTime = %f"), AnimSavedArray[0].playTime,currTime);
// 	}
	
	//delTime=0;
// 	UE_LOG(LogTemp,Warning,TEXT("DelTime = %f"),delTime); 
// 	UE_LOG(LogTemp, Warning, TEXT("DelTimeSeconds = %f"), GetWorld()->DeltaTimeSeconds);
// 	if(AnimLibWidget->GetAnimSequence(AnimSavedArray[0].Animindex)->GetPlayLength() >=0)
// 	{
// 		UE_LOG(LogTemp,Warning,TEXT("SequenceTime "));}
// 	else
// 		UE_LOG(LogTemp, Warning, TEXT("Sequence import error, %d"), AnimSavedArray[0].Animindex);
// 	while (delTime <= 1)
// 	{
// 		UE_LOG(LogTemp, Warning, TEXT("time : %f"),delTime);
// 		delTime+=
;
// 	}
		
	//while(다음 Mark까지 distance가 남았을 동안)
	//{
	// 걸어야한다.
	
// 		DistanceToTarget = FVector::Distance(CurrActor->GetActorLocation(), AnimSavedArray[1].ActorLocation); //타깃과의 거리 측정
// 		dir = AnimSavedArray[1].ActorLocation - CurrActor->GetActorLocation();
// 		dir.Normalize();
// 		CurrActor->SetActorRotation(dir.Rotation());//액터가 다음 타깃을 향해 걸어가도록 방향설정
// 		CurrActor->SetActorLocation(CurrActor->GetActorLocation() + dir * GetWorld()->DeltaTimeSeconds * 10);
	
	
	// 1. SetActorLocation (실제 액터 위치 옮겨줘야하고)
	// 2. 1번에 맞춰 걷는 애니메이션이 재생되어야하며
	// 3. 걷는 동안 액터의 forward가 걷는 방향을 향해야한다.
	// 4. 남은 distance를 업데이트 시켜줘야한다.
	//} 목표에 도달하면 알아서 while break
	
	//도달한 이후 코드
	//해당 마크에 저장된 로테이션에 맞춰 돌아야한다.
	//1. SetActorRotation (실제 액터의 로테이션을 돌려줘야하고)
	//2. 서서히 돌아가야하는데 방법을 잘모르겠ㅅ슴
	//저장된 Rot에 맞췄다면 
	//해당 마크에 저장된 애니메이션을 플레이한다.

	//다음 타깃까지 걷는것, 그 타깃에 도착했을 때 rot을 맞추고 타깃에 맞는 애님을 출력하는 것이 반복되어야한다.

	
	
}

		

	

//Rotation 간의 각도 간격을 계산하는 함수
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

	// 현재 방향과 목표 방향 간의 회전 각도 계산
	float AngleDifference = CalculateRotationDifference(CurrentRotation, TargetRotation);

	// 회전 각도에 따라 액터 회전
	FRotator NewRotation = UKismetMathLibrary::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), RotSpeed);
	CurrActor->SetActorRotation(NewRotation);
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
	//currTime += InDeltaTime;
	//전체 플레이 순회
	
if (EntireMode)
{
	//UE_LOG(LogTemp,Warning,TEXT("gogo Entire!"));

	
	if(DistanceToTarget>10&&!isArrive) //목적지까지 도착하지 못했다면
	{ 
		//UE_LOG(LogTemp, Warning, TEXT("gogo Entire!"));
		FVector P0 = CurrActor->GetActorLocation();
		FVector VT = 200 * dir * InDeltaTime;
		FVector P = P0 + VT;
		CurrActor->SetActorLocation(P);
		DistanceToTarget = FVector::Distance(CurrActor->GetActorLocation(), AnimSavedArray[CurrMark + 1].ActorLocation);
		UE_LOG(LogTemp, Warning, TEXT("dist : %f"),DistanceToTarget);
		if (currTime == 0) // 타이머가 0초일때 플레이 워킹애님
			CurrActorSkeletal->PlayAnimation(WalkAnim, false);
		//워킹 애니메이션 플레이시간이 다 되었다면
		if (currTime > WalkAnim->GetPlayLength()) 
		{
			/*UE_LOG(LogTemp,Warning,TEXT("move Time!"));*/
			currTime = 0.0f; //아직 타깃에 도달하지 못했으므로 다시 재생한다.
		}
		else  //워킹 애니메이션 플레이시간 도중이라면
		{
			currTime += InDeltaTime; //타이머 시간 ++
	
		}
	}
	else //처음EntireMode 진입 or 목적지까지 도착했다면
	{
		isArrive = true;
		UE_LOG(LogTemp, Warning, TEXT("Mark# %d Access spot success!"),CurrMark);
		if(delTime == 0)
		CurrActorSkeletal->PlayAnimation(AnimLibWidget->GetAnimSequence(AnimSavedArray[CurrMark].Animindex),false);
		if (delTime < AnimSavedArray[CurrMark].playTime)
		{
			delTime+=InDeltaTime;
		}
		else
		{
			//anim play는 이곳에서요!
		}

		if(DistanceToTarget>0)  // 처음 Mode진입한건지 목적지 도착한건지 구분하기 위함
		{
			UE_LOG(LogTemp, Warning, TEXT("CurrMark update!"));
			if(CurrMark+1<MarkNumber) 
			{
				CurrMark +=1;
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
// 		맨처음 Mark 애님을 플레이한다.
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
// 				//거리값 확인 로그
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

	case 0:
	{
		text_animName->SetText(FText::FromString("Idle"));
// 		if(isAdd)
// 		{ 
// 			FAnimSavedStruct newStruct;
// 			newStruct.ActorLocation = CurrActor->GetActorLocation();
// 			newStruct.ActorRotation = CurrActor->GetActorRotation();
// 			newStruct.Animindex = 5;
// 
// 			// 인덱스가 유효한 범위 내에 있는지 확인
// 			if (MarkNumber >= 0 && MarkNumber < AnimSavedArray.Num())
// 			{
// 				// 				UE_LOG(LogTemp, Warning, TEXT("correct index"));
// 
// 
// 								// 해당 인덱스의 구조체 요소를 참조
// 				FAnimSavedStruct& AccessedStruct = AnimSavedArray[MarkNumber];
// 
// 				// 해당 인덱스의 구조체 요소에 값을 할당
// 				AccessedStruct.ActorLocation = newStruct.ActorLocation;
// 				AccessedStruct.ActorRotation = newStruct.ActorRotation;
// 				AccessedStruct.Animindex = newStruct.Animindex;
// 				/*	UE_LOG(LogTemp, Warning, TEXT("Mark# %d : %d"), MarkNumber, AnimSavedArray[MarkNumber].Animindex);*/
// 			}
// 			else//인덱스가 유효하지 않다면...
// 			{
// 				if (MarkNumber < AnimSavedArray.Num())
// 				{
// 					AnimSavedArray.Add(newStruct);
// 					UE_LOG(LogTemp, Warning, TEXT("%d"), AnimSavedArray[MarkNumber].Animindex);
// 				}
// 				else
// 					UE_LOG(LogTemp, Warning, TEXT("index error!!"));
// 			}
// 		}
// 		isAdd=false;
		break;

	}
	case 1:
		/*FButtonStyle ButtonStyle = btn_animSelection->WidgetStyle;*/
		{
			text_animName->SetText(FText::FromString("Sit On Ground"));
// 			if(isAdd)
// 			{ 
// 				//새 구조체 요소 생성
// 				FAnimSavedStruct newStruct;
// 				newStruct.ActorLocation = CurrActor->GetActorLocation();
// 				newStruct.ActorRotation = CurrActor->GetActorRotation();
// 				newStruct.Animindex = 1;
// 		
// 				// 인덱스가 유효한 범위 내에 있는지 확인
// 				if (MarkNumber>= 0 && MarkNumber < AnimSavedArray.Num())
// 				{
// 	// 				UE_LOG(LogTemp,Warning,TEXT("correct index"));
// 			
// 
// 					// 해당 인덱스의 구조체 요소를 참조
// 					FAnimSavedStruct& AccessedStruct = AnimSavedArray[MarkNumber];
// 
// 	 				// 해당 인덱스의 구조체 요소에 값을 할당
// 					AccessedStruct.ActorLocation = newStruct.ActorLocation;
// 					AccessedStruct.ActorRotation = newStruct.ActorRotation;
// 		 			AccessedStruct.Animindex = newStruct.Animindex;
// 				/*	UE_LOG(LogTemp, Warning, TEXT("Mark# %d : %d"), MarkNumber, AnimSavedArray[MarkNumber].Animindex);*/
// 																}
// 				else //인덱스가 유효하지 않다면...
// 				{
// 					if(MarkNumber < AnimSavedArray.Num())
// 					{ 
// 						AnimSavedArray.Add(newStruct);
// 						UE_LOG(LogTemp, Warning, TEXT("%d"), AnimSavedArray[MarkNumber].Animindex);
// 					}
// 					else
// 						UE_LOG(LogTemp, Warning, TEXT("index error!!"));
// 				}
// 			}
		break;
		}
	case 2:
		{
			text_animName->SetText(FText::FromString("Sit On Chair"));
// 			FAnimSavedStruct newStruct;
// 			newStruct.ActorLocation = CurrActor->GetActorLocation();
// 			newStruct.ActorRotation = CurrActor->GetActorRotation();
// 			newStruct.Animindex = 2;
// 			
// 			// 인덱스가 유효한 범위 내에 있는지 확인
// 			if (MarkNumber >= 0 && MarkNumber < AnimSavedArray.Num())
// 			{
// // 				UE_LOG(LogTemp, Warning, TEXT("correct index"));
// 
// 
// 				// 해당 인덱스의 구조체 요소를 참조
// 				FAnimSavedStruct& AccessedStruct = AnimSavedArray[MarkNumber];
// 
// 				// 해당 인덱스의 구조체 요소에 값을 할당
// 				AccessedStruct.ActorLocation = newStruct.ActorLocation;
// 				AccessedStruct.ActorRotation = newStruct.ActorRotation;
// 				AccessedStruct.Animindex = newStruct.Animindex;
// 				/*UE_LOG(LogTemp, Warning, TEXT("Mark# %d : %d"),MarkNumber, AnimSavedArray[MarkNumber].Animindex);*/
// 			}
// 			else//인덱스가 유효하지 않다면...
// 			{
// 				if (MarkNumber < AnimSavedArray.Num())
// 				{
// 					AnimSavedArray.Add(newStruct);
// 					UE_LOG(LogTemp, Warning, TEXT("%d"), AnimSavedArray[MarkNumber].Animindex);
// 				}
// 				else
// 					UE_LOG(LogTemp, Warning, TEXT("index error!!"));
// 			}
			break;
		}
	
	case 3:
		{
			text_animName->SetText(FText::FromString("Standing Talk"));
			
// 			FAnimSavedStruct newStruct;
// 			newStruct.ActorLocation = CurrActor->GetActorLocation();
// 			newStruct.ActorRotation = CurrActor->GetActorRotation();
// 			newStruct.Animindex = 3;
// 
// 			// 인덱스가 유효한 범위 내에 있는지 확인
// 			if (MarkNumber >= 0 && MarkNumber < AnimSavedArray.Num())
// 			{
// 				/*UE_LOG(LogTemp, Warning, TEXT("correct index"));*/
// 
// 
// 				// 해당 인덱스의 구조체 요소를 참조
// 				FAnimSavedStruct& AccessedStruct = AnimSavedArray[MarkNumber];
// 
// 				// 해당 인덱스의 구조체 요소에 값을 할당
// 				AccessedStruct.ActorLocation = newStruct.ActorLocation;
// 				AccessedStruct.ActorRotation = newStruct.ActorRotation;
// 				AccessedStruct.Animindex = newStruct.Animindex;
// 			/*	UE_LOG(LogTemp, Warning, TEXT("Mark# %d : %d"), MarkNumber, AnimSavedArray[MarkNumber].Animindex);*/
// 			}
// 			else//인덱스가 유효하지 않다면...
// 			{
// 				if (MarkNumber < AnimSavedArray.Num())
// 				{
// 					AnimSavedArray.Add(newStruct);
// 					UE_LOG(LogTemp, Warning, TEXT("%d"), AnimSavedArray[MarkNumber].Animindex);
// 				}
// 				else
// 					UE_LOG(LogTemp, Warning, TEXT("index error!!"));
// 			}
			break;
		}

	case 4:
		{
			text_animName->SetText(FText::FromString("Standing Clap"));

// 			FAnimSavedStruct newStruct;
// 			newStruct.ActorLocation = CurrActor->GetActorLocation();
// 			newStruct.ActorRotation = CurrActor->GetActorRotation();
// 			newStruct.Animindex = 4;
// 
// 			// 인덱스가 유효한 범위 내에 있는지 확인
// 			if (MarkNumber >= 0 && MarkNumber < AnimSavedArray.Num())
// 			{
// // 				UE_LOG(LogTemp, Warning, TEXT("correct index"));
// 
// 
// 				// 해당 인덱스의 구조체 요소를 참조
// 				FAnimSavedStruct& AccessedStruct = AnimSavedArray[MarkNumber];
// 
// 				// 해당 인덱스의 구조체 요소에 값을 할당
// 				AccessedStruct.ActorLocation = newStruct.ActorLocation;
// 				AccessedStruct.ActorRotation = newStruct.ActorRotation;
// 				AccessedStruct.Animindex = newStruct.Animindex;
// 				/*UE_LOG(LogTemp, Warning, TEXT("Mark# %d : %d"), MarkNumber, AnimSavedArray[MarkNumber].Animindex);*/
// 			}
// 			else//인덱스가 유효하지 않다면...
// 			{
// 				if (MarkNumber < AnimSavedArray.Num())
// 				{
// 					AnimSavedArray.Add(newStruct);
// 					UE_LOG(LogTemp, Warning, TEXT("%d"), AnimSavedArray[MarkNumber].Animindex);
// 				}
// 				else
// 					UE_LOG(LogTemp, Warning, TEXT("index error!!"));
// 			}
			break;
		}
		
	case 5:
		{
			text_animName->SetText(FText::FromString("Idle"));

// 			FAnimSavedStruct newStruct;
// 			newStruct.ActorLocation = CurrActor->GetActorLocation();
// 			newStruct.ActorRotation = CurrActor->GetActorRotation();
// 			newStruct.Animindex = 5;
// 
// 			// 인덱스가 유효한 범위 내에 있는지 확인
// 			if (MarkNumber >= 0 && MarkNumber < AnimSavedArray.Num())
// 			{
// // 				UE_LOG(LogTemp, Warning, TEXT("correct index"));
// 
// 
// 				// 해당 인덱스의 구조체 요소를 참조
// 				FAnimSavedStruct& AccessedStruct = AnimSavedArray[MarkNumber];
// 
// 				// 해당 인덱스의 구조체 요소에 값을 할당
// 				AccessedStruct.ActorLocation = newStruct.ActorLocation;
// 				AccessedStruct.ActorRotation = newStruct.ActorRotation;
// 				AccessedStruct.Animindex = newStruct.Animindex;
// 			/*	UE_LOG(LogTemp, Warning, TEXT("Mark# %d : %d"), MarkNumber, AnimSavedArray[MarkNumber].Animindex);*/
// 			}
// 			else//인덱스가 유효하지 않다면...
// 			{
// 				if (MarkNumber < AnimSavedArray.Num())
// 				{
// 					AnimSavedArray.Add(newStruct);
// 					UE_LOG(LogTemp, Warning, TEXT("%d"), AnimSavedArray[MarkNumber].Animindex);
// 				}
// 				else
// 					UE_LOG(LogTemp, Warning, TEXT("index error!!"));
// 			}
// 		
			break;
		}
	
	case 6:
		{
			text_animName->SetText(FText::FromString("Walk"));

// 			FAnimSavedStruct newStruct;
// 			newStruct.ActorLocation = CurrActor->GetActorLocation();
// 			newStruct.ActorRotation = CurrActor->GetActorRotation();
// 			newStruct.Animindex = 6;
// 
// 			// 인덱스가 유효한 범위 내에 있는지 확인
// 			if (MarkNumber >= 0 && MarkNumber < AnimSavedArray.Num())
// 			{
// // 				UE_LOG(LogTemp, Warning, TEXT("correct index"));
// 
// 
// 				// 해당 인덱스의 구조체 요소를 참조
// 				FAnimSavedStruct& AccessedStruct = AnimSavedArray[MarkNumber];
// 
// 				// 해당 인덱스의 구조체 요소에 값을 할당
// 				AccessedStruct.ActorLocation = newStruct.ActorLocation;
// 				AccessedStruct.ActorRotation = newStruct.ActorRotation;
// 				AccessedStruct.Animindex = newStruct.Animindex;
// 				/*UE_LOG(LogTemp, Warning, TEXT("Mark# %d : %d"), MarkNumber, AnimSavedArray[MarkNumber].Animindex);*/
// 			}
// 			else//인덱스가 유효하지 않다면...
// 			{
// 				if (MarkNumber < AnimSavedArray.Num())
// 				{
// 					AnimSavedArray.Add(newStruct);
// 					UE_LOG(LogTemp, Warning, TEXT("%d"), AnimSavedArray[MarkNumber].Animindex);
// 				}
// 				else
// 					UE_LOG(LogTemp, Warning, TEXT("index error!!"));
// 			}

			break;
		}

	default:
		{
			text_animName->SetText(FText::FromString("Idle"));
// 			if(isAdd)
// 			{ 
// 			FAnimSavedStruct newStruct;
// 			newStruct.ActorLocation = CurrActor->GetActorLocation();
// 			newStruct.ActorRotation = CurrActor->GetActorRotation();
// 			newStruct.Animindex = 5;
// 
// 			// 인덱스가 유효한 범위 내에 있는지 확인
// 			if (MarkNumber >= 0 && MarkNumber < AnimSavedArray.Num())
// 			{
// 				// 				UE_LOG(LogTemp, Warning, TEXT("correct index"));
// 
// 
// 								// 해당 인덱스의 구조체 요소를 참조
// 				FAnimSavedStruct& AccessedStruct = AnimSavedArray[MarkNumber];
// 
// 				// 해당 인덱스의 구조체 요소에 값을 할당
// 				AccessedStruct.ActorLocation = newStruct.ActorLocation;
// 				AccessedStruct.ActorRotation = newStruct.ActorRotation;
// 				AccessedStruct.Animindex = newStruct.Animindex;
// 				/*	UE_LOG(LogTemp, Warning, TEXT("Mark# %d : %d"), MarkNumber, AnimSavedArray[MarkNumber].Animindex);*/
// 			}
// 			else//인덱스가 유효하지 않다면...
// 			{
// 				if (MarkNumber < AnimSavedArray.Num())
// 				{
// 					AnimSavedArray.Add(newStruct);
// 					UE_LOG(LogTemp, Warning, TEXT("%d"), AnimSavedArray[MarkNumber].Animindex);
// 				}
// 				else
// 					UE_LOG(LogTemp, Warning, TEXT("index error!!"));
// 			}
// 			}
			break;

		}
	}
}

