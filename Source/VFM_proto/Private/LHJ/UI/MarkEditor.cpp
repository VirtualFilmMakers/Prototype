// Fill out your copyright notice in the Description page of Project Settings.


#include "MarkEditor.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "AnimLibrary.h"
#include "Components/Slider.h"


void UMarkEditor::NativeConstruct()
{
	Super::NativeConstruct(); //MarkEditor�� ���ܾ� ����Ǵ� �Լ�

	//UE_LOG(LogTemp,Warning,TEXT("MarkEditor perfect!"));
	World = GetWorld();
	btn_animSelection->OnClicked.AddDynamic(this, &UMarkEditor::OnClickAnimLib);
	slider_holdTime->OnValueChanged.AddDynamic(this, &UMarkEditor::OnSliderMoved);

	pc = GetWorld()->GetFirstPlayerController();
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
/*�� �� : 
* �÷��̾� ��Ʈ�ѷ����� ���콺 �� �̺�Ʈ �޾ƿ���
* ���� �������� float������ �޾ƿ���
* ���忡 ��ġ�� ��Ÿ�޸� �޾ƿ���
* ��Ÿ�޸� yaw �� �ٲٱ� (float�� �޾ƿ� ������)
* 
*/