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

	//UE_LOG(LogTemp,Warning,TEXT("MarkEditor perfect!"));
	World = GetWorld();
	btn_animSelection->OnClicked.AddDynamic(this, &UMarkEditor::OnClickAnimLib);
	slider_holdTime->OnValueChanged.AddDynamic(this, &UMarkEditor::OnSliderMoved);
	btn_addMark->OnClicked.AddDynamic(this, &UMarkEditor::OnClickAddMark);

	pc = GetWorld()->GetFirstPlayerController();
	
	player = Cast<AOSY_TESTCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AOSY_TESTCharacter::StaticClass()));
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
	
	
}


void UMarkEditor::SetCurrActor(AMHActorA* temp)
{
	CurrActor = temp;
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
	text_sliderCount->SetText(FText::AsNumber((int32)value));
	
}



//TICK -> Animation Selection Input 받아와서 text 변경
void UMarkEditor::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	//Super::NativeTick(MyGeometry, InDeltaTime);
	if(AnimLibWidget!=nullptr)
	InputAnimState = AnimLibWidget->GetAnimInfo();

	CurrActor->SetActorLocation(player->AddMarkLocation);

	switch (InputAnimState)
	{
	case 1:
		/*FButtonStyle ButtonStyle = btn_animSelection->WidgetStyle;*/
		text_animName->SetText(FText::FromString("Sit On Ground"));
		break;

	case 2:
		text_animName->SetText(FText::FromString("Sit On Chair"));
		break;
	
	case 3:
		text_animName->SetText(FText::FromString("Standing Talk"));
		break;

	case 4:
		text_animName->SetText(FText::FromString("Standing Clap"));
		break;
		
	case 5:
		text_animName->SetText(FText::FromString("Idle"));
		break;
	
	case 6:
		text_animName->SetText(FText::FromString("Walk"));
		break;

	default:
		break;
	}
}
