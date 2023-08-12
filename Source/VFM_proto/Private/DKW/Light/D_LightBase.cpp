// Fill out your copyright notice in the Description page of Project Settings.


#include "D_LightBase.h"
#include "Blueprint/UserWidget.h"

// Sets default values
AD_LightBase::AD_LightBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AD_LightBase::BeginPlay()
{
	Super::BeginPlay();
	
     
    //if (LightWidgetSource)
    //{
    //    // Create an instance of the provided UMG widget class
    //    WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), LightWidgetSource);
    //    if (WidgetInstance)
    //    {
    //        WidgetInstance->AddToViewport(); // Add the widget to the viewport
    //    }
    //}
   
    //WidgetInstance->SetPositionInViewport(FVector2D(1600,50));
}

// Called every frame
void AD_LightBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

