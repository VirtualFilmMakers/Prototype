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
	
	// 카메라를 배치하고 싶다
	// 필요속성 : 카메라, 카메라 위치를 잡아줄 스프링암

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* springArmComp;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* playerCam;

	

public://플레이어 입력에 관한 부분
	// 기존 입력 방식
	float speed=500;
	FVector Direction;
	void Horizontal(float value);
	void Vertical(float value);
	void jump();
	
	//기존 카메라 움직임 방식

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
	


	//메타휴면 C++로
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
