// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseComponent.h"
#include "O_BuildSystem.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VFM_PROTO_API UO_BuildSystem : public UPlayerBaseComponent
{
	GENERATED_BODY()

	public:	
	// Sets default values for this component's properties
	UO_BuildSystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void SetupInputBinding(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enhanced Input")
	class UInputAction* ia_BuildPlace1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enhanced Input")
	class UInputAction* ia_BuildPlace2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enhanced Input")
	class UInputAction* ia_BuildPreview1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enhanced Input")
	class UInputAction* ia_BuildPreview2;


	//----------------------------
	void BuildPreview1();
	void BuildPlace1();
	UFUNCTION(Server,Reliable)
	void ServerBuildPlace1(const FVector& bLocation, const FVector& bDirection);
	UFUNCTION(NetMulticast,Reliable)
	void MulticastBuildPlace1(const FVector& bLocation, const FVector& bDirection);
	
	//------------------------------------
	void BuildPreview2();
	void BuildPlace2();
	UFUNCTION(Server,Reliable)
	void ServerBuildPlace2(const FVector& bLocation, const FVector& bDirection);
	UFUNCTION(NetMulticast,Reliable)
	void MulticastBuildPlace2(const FVector& bLocation, const FVector& bDirection);
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MySettings")
	FTransform BuildPriviewTransform;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MySettings")
	bool DoOnce=false;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MySettings")
	TSubclassOf<class AO_SpawnActor> FloorFactory;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MySettings")
	TSubclassOf<class AO_SpawnActor> WallFactory;
	
		
	
};
