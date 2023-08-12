// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "OSY_TESTCharacter.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FInputBindingDelegate, class UInputComponent*);

UCLASS()
class VFM_PROTO_API AOSY_TESTCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AOSY_TESTCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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

	

public://�÷��̾� �Է¿� ���� �κ�
	// ���� �Է� ���
	float speed=500;
	FVector Direction;
	void Horizontal(float value);
	void Vertical(float value);
	void jump();
	
	//���� ī�޶� ������ ���

	void CameraZoom(float value);

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

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MySettings")
	class UBoxComponent* compBox;


	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Enhanced Input")
	class UInputMappingContext* InputMapping;

	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enhanced Input")
		class UInputAction* ia_Jump;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enhanced Input")
	class UInputAction* ia_Posses;
	


	//��Ÿ�޸� C++��
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MySettings")
	class USceneComponent* compRoot;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MySettings")
	class USkeletalMeshComponent *compBody;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MySettings")
	class ACharacter* testPawn;

// delegate
	FInputBindingDelegate onInputBindingDelegate;

// LineTrace-----------------------------
	void LineTraceFire();
// Posses
	UFUNCTION()
	void ChangePosessInput();

	UFUNCTION(BlueprintCallable)
	void ChangePosses(ACharacter* NewPawn);
};
