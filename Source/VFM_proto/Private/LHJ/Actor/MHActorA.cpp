// Fill out your copyright notice in the Description page of Project Settings.


#include "MHActorA.h"
#include "D_ControllableAsset.h"
#include "MarkEditor.h"
#include "OSY_TESTCharacter.h"

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

	
}

// Called every frame
void AMHActorA::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMHActorA::CloseAssetPanel_Implementation(AActor* AssetWithControlPanel)
{
	ID_ControllableAsset::CloseAssetPanel_Implementation(AssetWithControlPanel);
	
	
	/*markEditorWidget->SetVisibility(ESlateVisibility::Hidden);*/
}

void AMHActorA::OpenAssetPanel_Implementation(AActor* AssetWithControlPanel)
{
	ID_ControllableAsset::OpenAssetPanel_Implementation(AssetWithControlPanel);
// 	UE_LOG(LogTemp, Warning, TEXT("Cooper ALIVE!!"));
	
	markEditorWidget->SetVisibility(ESlateVisibility::Visible);
	//Hover 되었는지 알 수 있는 함수 부분. Hover되었을때만 실행되는 함수 이기 때문임.
	//사용자를 받아와야한다. (컨트롤러 받아와서 케스트)
	/*player = Cast<AOSY_TESTCharacter>(pc);*/
	
	//사용자의 휠 값을 받아와야한다.
	
	
}
