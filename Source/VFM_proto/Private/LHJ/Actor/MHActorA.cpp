// Fill out your copyright notice in the Description page of Project Settings.


#include "MHActorA.h"
#include "D_ControllableAsset.h"
#include "MarkEditor.h"

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
	
	//TsubclassOf�� ������ MarkEditor������ ���� ���忡 ������ ����� �ش� ������ ����Ű�� �ּҸ� ��ȯ
	markEditorWidget = CreateWidget<UMarkEditor>(World, MarkEditorClass);
	
	/*UE_LOG(LogTemp, Warning, TEXT("Begin Cooper"));*/
	if (markEditorWidget != nullptr)
	{
		markEditorWidget->AddToViewport();
		UE_LOG(LogTemp,Warning,TEXT("created successfult Mark Widget!"));
		markEditorWidget->SetVisibility(ESlateVisibility::Hidden);
			//pc->SetInputMode(FInputModeGameAndUI());
	} //ȭ�鿡 �������

	
}

// Called every frame
void AMHActorA::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMHActorA::CloseAssetPanel_Implementation(AActor* AssetWithControlPanel)
{
	ID_ControllableAsset::CloseAssetPanel_Implementation(AssetWithControlPanel);
	
	UE_LOG(LogTemp, Warning, TEXT("Cooper Widget Close!"));
	
	/*markEditorWidget->SetVisibility(ESlateVisibility::Hidden);*/
}

void AMHActorA::OpenAssetPanel_Implementation(AActor* AssetWithControlPanel)
{
	ID_ControllableAsset::OpenAssetPanel_Implementation(AssetWithControlPanel);
// 	UE_LOG(LogTemp, Warning, TEXT("Cooper ALIVE!!"));
	
	markEditorWidget->SetVisibility(ESlateVisibility::Visible);

}
