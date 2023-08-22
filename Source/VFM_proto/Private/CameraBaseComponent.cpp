// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraBaseComponent.h"

// Sets default values for this component's properties
UCameraBaseComponent::UCameraBaseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bWantsInitializeComponent = true;
}


void UCameraBaseComponent::InitializeComponent()
{
	Super::InitializeComponent();

	me = Cast<AO_CameraBase>(GetOwner());
	moveComp = me->GetCharacterMovement();

	//바인딩처리
	me->onCameraInputBindingDelegate.AddUObject(this, &UCameraBaseComponent::SetupInputBinding);
}

// Called when the game starts
void UCameraBaseComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCameraBaseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

