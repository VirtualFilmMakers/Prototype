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

	//UE_LOG(LogTemp,Warning,TEXT("MarkEditor perfect!"));
	World = GetWorld();
	btn_animSelection->OnClicked.AddDynamic(this, &UMarkEditor::OnClickAnimLib);
	slider_holdTime->OnValueChanged.AddDynamic(this, &UMarkEditor::OnSliderMoved);
	btn_addMark->OnClicked.AddDynamic(this, &UMarkEditor::OnClickAddMark);

	pc = GetWorld()->GetFirstPlayerController();
	
	player = Cast<AOSY_TESTCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AOSY_TESTCharacter::StaticClass()));
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


void UMarkEditor::SetCurrActor(AMHActorA* temp)
{
	CurrActor = temp;
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
	text_sliderCount->SetText(FText::AsNumber((int32)value));
	
}



//TICK -> Animation Selection Input �޾ƿͼ� text ����
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
