// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MHAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class VFM_PROTO_API UMHAnimInstance : public UAnimInstance
{
	GENERATED_BODY()


public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;	   

	//Get now this anim instance owner
	class APawn* owner;
	
	//Owner cast to MHActor for update property.
	class AMHActorA* InstanceHost;

	/*<------ val for logic----->*/
	//index 1�� SitOnGround
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MySettings)
	bool SitOnGround = false;

	//index 2�� SigOnChair
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MySettings)
	bool SitOnChair= false;

	//index 3�� StandingTalk
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MySettings)
	bool StandingTalk= false;

	//index 4�� StandingClap
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MySettings)
	bool StandingClap= false;

	//index 5�� Idle
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MySettings)
	bool Idle = false;

	//index 6�� Walking
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MySettings)
	bool Walking = false;


	//--------------------FUNCTION----------
public:
	UFUNCTION()
	void UpdateProperties();

};
