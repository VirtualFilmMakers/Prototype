// Fill out your copyright notice in the Description page of Project Settings.


#include "MHActorA.h"
#include "D_ControllableAsset.h"
#include "MarkEditor.h"
#include "OSY_TESTCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerZoom.h"
#include "GameFramework/PlayerInput.h"

// Sets default values
AMHActorA::AMHActorA()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
// 	UE_LOG(LogTemp, Warning, TEXT("Cooper Created!"));

}

// Called when the game starts or when spawned
void AMHActorA::BeginPlay()
{
	Super::BeginPlay();
	
	World = GetWorld();
	pc = GetWorld()->GetFirstPlayerController();

	if(pc != nullptr) UE_LOG(LogTemp, Warning, TEXT("PC good job"));
	
	//TsubclassOf로 가져온 MarkEditor정보를 통해 월드에 위젯을 만들고 해당 위젯을 가르키는 주소를 반환
	markEditorWidget = CreateWidget<UMarkEditor>(World, MarkEditorClass);
	
	/*UE_LOG(LogTemp, Warning, TEXT("Begin Cooper"));*/
	if (markEditorWidget != nullptr)
	{
		markEditorWidget->AddToViewport();
		UE_LOG(LogTemp,Warning,TEXT("created successfult Mark Widget!"));
		markEditorWidget->SetVisibility(ESlateVisibility::Hidden);
			//pc->SetInputMode(FInputModeGameAndUI());
	} //화면에 띄워놓기

	player = Cast<AOSY_TESTCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AOSY_TESTCharacter::StaticClass()));

	if (player != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("hello player!"));
	}
	else UE_LOG(LogTemp, Warning, TEXT("player Load fail.."));
	
	player->CurrActor = this; //현재 호버되어 있는 메타휴먼은 저에요...!
}

// Called every frame
void AMHActorA::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MouseWheelValue = player->GetComponentByClass<UPlayerZoom>()->GetZoomValue();
	/*UE_LOG(LogTemp,Warning,TEXT("%f"),MouseWheelValue);*/

	/*!! 플레이어 줌 멈추는 로직 필요!!*/

	if(MouseWheelValue!=0.0f){
	this->SetActorRotation(FRotator(0.0f,this->GetActorRotation().Yaw + MouseWheelValue*5.0f,0.0f));
	}
}

void AMHActorA::CloseAssetPanel_Implementation(AActor* AssetWithControlPanel)
{
	ID_ControllableAsset::CloseAssetPanel_Implementation(AssetWithControlPanel);
	
	
	markEditorWidget->SetVisibility(ESlateVisibility::Hidden);
}

void AMHActorA::OpenAssetPanel_Implementation(AActor* AssetWithControlPanel)
{
	ID_ControllableAsset::OpenAssetPanel_Implementation(AssetWithControlPanel);
// 	UE_LOG(LogTemp, Warning, TEXT("Cooper ALIVE!!"));
	
	markEditorWidget->SetVisibility(ESlateVisibility::Visible);
	markEditorWidget->SetCurrActor(this); //현재 스폰되어 있는 메타휴먼정보를 MarkEditor에게 넘겨주기 위함.
}

//Mark Editor에게 나 누구야 알려주기(완)
//그거 기반으로 스폰하기
//애니메이션 세이브드 구조체 만들기
// 