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

	// ī�޶� ��ġ�ϰ� �ʹ�
	// �ʿ�Ӽ� : ī�޶�, ī�޶� ��ġ�� ����� ��������

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* springArmComp;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* playerCam;

public:
// �÷��̾� �Է¿� ���� �κ�
// ���� �Է� ���
	float speed = 500;
	FVector Direction;
	//void Horizontal(float value);
	//void Vertical(float value);
	//void jump();


	//���� ī�޶� ������ ���

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
