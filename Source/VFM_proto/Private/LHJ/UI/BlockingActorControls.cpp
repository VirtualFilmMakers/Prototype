// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockingActorControls.h"
#include "Components/Button.h"

void UBlockingActorControls::NativeConstruct()
{
	Super::NativeConstruct();

	btn_addMark->OnClicked.AddDynamic(this, &UBlockingActorControls::OnClickAddMark);
}

void UBlockingActorControls::OnClickAddMark()
{
	
}

void UBlockingActorControls::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{

}
