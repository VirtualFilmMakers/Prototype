// Fill out your copyright notice in the Description page of Project Settings.


#include "MarkEditor.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "AnimLibrary.h"
#include "Components/Slider.h"


void UMarkEditor::NativeConstruct()
{
	Super::NativeConstruct(); //MarkEditor가 생겨야 실행되는 함수

	//UE_LOG(LogTemp,Warning,TEXT("MarkEditor perfect!"));
	World = GetWorld();
	btn_animSelection->OnClicked.AddDynamic(this, &UMarkEditor::OnClickAnimLib);
	slider_holdTime->OnValueChanged.AddDynamic(this, &UMarkEditor::OnSliderMoved);

	pc = GetWorld()->GetFirstPlayerController();
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

void UMarkEditor::OnSliderMoved(float value)
{
	text_sliderCount->SetText(FText::AsNumber((int32)value));
	
}

void UMarkEditor::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	//Super::NativeTick(MyGeometry, InDeltaTime);
	if(AnimLibWidget!=nullptr)
	InputAnimState = AnimLibWidget->GetAnimInfo();

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
/*할 것 : 
* 플레이어 컨트롤러에서 마우스 휠 이벤트 받아오기
* 휠의 움직임을 float값으로 받아오기
* 월드에 배치된 메타휴먼 받아오기
* 메타휴먼 yaw 값 바꾸기 (float값 받아온 것으로)
* 
*/