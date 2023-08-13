// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
//#include <GameFramework/Character.h>
#include "D_AssetControlPlayer.generated.h"

UCLASS()
class VFM_PROTO_API AD_AssetControlPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AD_AssetControlPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	//virtual void MouseLeftAction();
	//virtual void MouseLeftReleasedAction();
	//virtual void MouseRightAction();

	//virtual void KeyQ();
	//virtual void KeyE();
	//virtual void KeyX();
	//virtual void KeyC();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 카메라를 배치하고 싶다
	// 필요속성 : 카메라, 카메라 위치를 잡아줄 스프링암

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* springArmComp;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* playerCam;

public:
// 플레이어 입력에 관한 부분
// 기존 입력 방식
	float speed = 500;
	FVector Direction;
	//void Horizontal(float value);
	//void Vertical(float value);
	//void jump();


	//기존 카메라 움직임 방식

	//void CameraZoom(float value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float MinZoomLength = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float MaxZoomLength = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float DefaultArmLength = 600.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float ZoomStep = 10.f;


public:	//EnhanecedInput

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Fly")
	int JumpCount;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Enhanced Input")
	class UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enhanced Input")
	class UInputAction* ia_Move;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enhanced Input")
	class UInputAction* ia_Look;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enhanced Input")
	class UInputAction* ia_Jump;
};
