// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "../../VFM_proto/public/D_ControllableAsset.h"
#include "MHActorA.generated.h"

UCLASS()
class VFM_PROTO_API AMHActorA : public APawn, public ID_ControllableAsset
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMHActorA();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
// 	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	UWorld* World = nullptr;
	UPROPERTY(EditAnywhere, Category = "My Settings")
	TSubclassOf<class UMarkEditor> MarkEditorClass; //MarkEditor class를 받아오기 위한 변수
	UPROPERTY()
	class UMarkEditor* markEditorWidget = nullptr;
	//플레이어컨트롤러를 받아올 변수 (사용자를 가져올 변수)
	UPROPERTY()
	APlayerController* pc = nullptr;
	UPROPERTY()
	class AOSY_TESTCharacter* player = nullptr;
	UPROPERTY()
	float MouseWheelValue = 0;
	
	UPROPERTY()
	FVector CurrActorLocation;


	/*-------  Animation State  ---------*/
	//index 1번 SitOnGround
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MySettings)
	bool SitOnGround = false;

	//index 2번 SigOnChair
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MySettings)
	bool SitOnChair= false;

	//index 3번 StandingTalk
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MySettings)
	bool StandingTalk= false;

	//index 4번 StandingClap
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MySettings)
	bool StandingClap= false;

	//index 5번 Idle
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MySettings)
	bool Idle = false;

	//index 6번 Walking
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MySettings)
	bool Walking = false;

	virtual void OpenAssetPanel_Implementation(AActor* AssetWithControlPanel) override;

	virtual void CloseAssetPanel_Implementation(AActor* AssetWithControlPanel) override;

public:

/* index#1 Sit On Ground Server Work */
	UFUNCTION(Reliable, Server, WithValidation)
	void StartSitOnGroundServer();	
	void StartSitOnGroundServer_Implementation();
	bool StartSitOnGroundServer_Validate();

	UFUNCTION(Reliable, NetMulticast)
	void StartSitOnGroundMulticast();
	void StartSitOnGroundMulticast_Implementation();


/* index#2 Sit On Chair Server Work */
	UFUNCTION(Reliable, Server, WithValidation)
	void StartSitOnChairServer();	
	void StartSitOnChairServer_Implementation();
	bool StartSitOnChairServer_Validate();

	UFUNCTION(Reliable, NetMulticast)
	void StartSitOnChairMulticast();
	void StartSitOnChairMulticast_Implementation();

/* index#3 Standing Talk Server Work */
	UFUNCTION(Reliable, Server, WithValidation)
	void StartStandingTalkServer();	
	void StartStandingTalkServer_Implementation();
	bool StartStandingTalkServer_Validate();

	UFUNCTION(Reliable, NetMulticast)
	void StartStandingTalkMulticast();
	void StartStandingTalkMulticast_Implementation();

/* index#4 Standing Clap Server Work */
	UFUNCTION(Reliable, Server, WithValidation)
	void StartStandingClapServer();	
	void StartStandingClapServer_Implementation();
	bool StartStandingClapServer_Validate();

	UFUNCTION(Reliable, NetMulticast)
	void StartStandingClapMulticast();
	void StartStandingClapMulticast_Implementation();

/* index#5 idle Server Work */
	UFUNCTION(Reliable, Server, WithValidation)
	void StartIdleServer();	
	void StartIdleServer_Implementation();
	bool StartIdleServer_Validate();

	UFUNCTION(Reliable, NetMulticast)
	void StartIdleMulticast();
	void StartIdleMulticast_Implementation();

/* index#6 Walking server Work */
	UFUNCTION(Reliable, Server, WithValidation)
	void StartWalkServer();	
	void StartWalkServer_Implementation();
	bool StartWalkServer_Validate();

	UFUNCTION(Reliable, NetMulticast)
	void StartWalkMulticast();
	void StartWalkMulticast_Implementation();


/* ALL STOP Anim */
	UFUNCTION(Reliable, Server, WithValidation)
	void AllStopAnimServer();	
	void AllStopAnimServer_Implementation();
	bool AllStopAnimServer_Validate();

	UFUNCTION(Reliable, NetMulticast)
	void AllStopAnimMulticast();
	void AllStopAnimMulticast_Implementation();

public:
	UFUNCTION()
	void IndexPlayAnim(int idx);
	UFUNCTION()
	void IndexStopAnim();

};	

