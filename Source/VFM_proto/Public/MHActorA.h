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

	virtual void OpenAssetPanel_Implementation(AActor* AssetWithControlPanel) override;

	virtual void CloseAssetPanel_Implementation(AActor* AssetWithControlPanel) override;


};
