// Fill out your copyright notice in the Description page of Project Settings.


#include "MHActorA.h"
#include "D_ControllableAsset.h"
#include "MarkEditor.h"
#include "OSY_TESTCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerZoom.h"
#include "GameFramework/PlayerInput.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AMHActorA::AMHActorA()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
// 	UE_LOG(LogTemp, Warning, TEXT("Cooper Created!"));
	bReplicates = true;
	SetReplicateMovement(true);
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

// 1번
void AMHActorA::StartSitOnGroundServer_Implementation()
{
	StartSitOnGroundMulticast();
}

bool AMHActorA::StartSitOnGroundServer_Validate()
{
	return true;
}

void AMHActorA::StartSitOnGroundMulticast_Implementation()
{
	SitOnGround = true;
	SitOnChair = false;
	StandingTalk = false;
	StandingClap = false;
	Idle = false;
	Walking = false;
}

//2번
void AMHActorA::StartSitOnChairServer_Implementation()
{
	StartSitOnChairMulticast();
}

bool AMHActorA::StartSitOnChairServer_Validate()
{
	return true;
}

void AMHActorA::StartSitOnChairMulticast_Implementation()
{
	SitOnGround = false;
	SitOnChair = true;
	StandingTalk = false;
	StandingClap = false;
	Idle = false;
	Walking = false;
}

//3번
void AMHActorA::StartStandingTalkServer_Implementation()
{
	StartStandingTalkMulticast();
}

bool AMHActorA::StartStandingTalkServer_Validate()
{
	return true;
}

void AMHActorA::StartStandingTalkMulticast_Implementation()
{
	SitOnGround = false;
	SitOnChair = false;
	StandingTalk = true;
	StandingClap = false;
	Idle = false;
	Walking = false;
}


//4번
void AMHActorA::StartStandingClapServer_Implementation()
{
	StartStandingClapMulticast();
}

bool AMHActorA::StartStandingClapServer_Validate()
{
	return true;
}

void AMHActorA::StartStandingClapMulticast_Implementation()
{
	SitOnGround = false;
	SitOnChair = false;
	StandingTalk = false;
	StandingClap = true;
	Idle = false;
	Walking = false;
}

//5번

void AMHActorA::StartIdleServer_Implementation()
{
	StartIdleMulticast();
}

bool AMHActorA::StartIdleServer_Validate()
{
	return true;
}

void AMHActorA::StartIdleMulticast_Implementation()
{
	SitOnGround = false;
	SitOnChair = false;
	StandingTalk = false;
	StandingClap = false;
	Idle = true;
	Walking = false;
}


//6번
void AMHActorA::StartWalkServer_Implementation()
{
	StartWalkMulticast();
}

bool AMHActorA::StartWalkServer_Validate()
{
	return true;
}

void AMHActorA::StartWalkMulticast_Implementation()
{
	SitOnGround = false;
	SitOnChair = false;
	StandingTalk = false;
	StandingClap = false;
	Idle = false;
	Walking = true;
}


void AMHActorA::IndexPlayAnim(int idx)
{
	switch (idx)
	{
		case 1:
		{
			StartSitOnGroundServer();
			break;
		}
		case 2:
		{
			StartSitOnChairServer();
			break;
		}
		case 3:
		{
			StartStandingTalkServer();
			break;
		}
		case 4:
		{
			StartStandingClapServer();
			break;
		}
		case 5:
		{
			StartIdleServer();
			break;
		}
		case 6:
		{
			StartWalkServer();
			break;
		}
		default:
		{
			StartIdleServer();
			break;
		}
	}
}

/*------------ Asset Panel  ---------------*/
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
