// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "OSY_PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class VFM_PROTO_API UOSY_PlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	// Tick ó�� �������� ����
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


	//�÷��̾ ���߿� �ִ��� üũ�ϴ� �Ұ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MySettings)
	bool bInAir= false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MySettings)
	bool bIsStart= true;

	// �÷��̾� �̵��ӵ�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=MySettings)
	float speed = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=MySettings)
	float direction = 0;
};
