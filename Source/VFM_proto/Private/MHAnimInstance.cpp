// Fill out your copyright notice in the Description page of Project Settings.


#include "MHAnimInstance.h"
#include "MHActorA.h"

//begin play
void UMHAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	owner = TryGetPawnOwner();
	//���� �� �ִ��ν��Ͻ��� ����� ���̷�Ż�� ������ �����´�.

	InstanceHost = Cast<AMHActorA>(owner);
	//owner�� ���� ���� ������ mhactor�� cast�ؿ´�.
	//�̰� ���� property�� ������Ʈ �ϰ� ��Ȳ�� �°� �ִ��÷����� ����

	
}

//tick
void UMHAnimInstance::NativeUpdateAnimation(float DeltaSeconds) 
{	
	Super::NativeUpdateAnimation(DeltaSeconds);
	//���̷�Ż�� ���� �� ������ ���� ������Ʈ�� ����
	// �� Ÿ�ֿ̹� ���ϴ� �ִϸ��̼��� �÷����� �� �ִ�.
	if(InstanceHost!=nullptr)
		UpdateProperties();
	
}

//�ִϸ��̼� �÷��̸� ���� ������Ƽ ������Ʈ �Լ�
void UMHAnimInstance::UpdateProperties()
{
	SitOnGround = InstanceHost->SitOnGround;
	SitOnChair = InstanceHost->SitOnChair;
	StandingTalk = InstanceHost->StandingTalk;
	StandingClap = InstanceHost->StandingClap;
	Idle = InstanceHost->Idle;
	Walking = InstanceHost->Walking;
}

