// Fill out your copyright notice in the Description page of Project Settings.


#include "MHAnimInstance.h"
#include "MHActorA.h"

//begin play
void UMHAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	owner = TryGetPawnOwner();
	//현재 이 애님인스턴스가 적용된 스켈레탈의 주인을 가져온다.

	InstanceHost = Cast<AMHActorA>(owner);
	//owner를 통해 현재 꺼내진 mhactor를 cast해온다.
	//이걸 통해 property를 업데이트 하고 상황에 맞게 애님플레이할 예정

	
}

//tick
void UMHAnimInstance::NativeUpdateAnimation(float DeltaSeconds) 
{	
	Super::NativeUpdateAnimation(DeltaSeconds);
	//스켈레탈의 주인 내 구현된 변수 업데이트를 통해
	// 각 타이밍에 원하는 애니메이션을 플레이할 수 있다.
	if(InstanceHost!=nullptr)
		UpdateProperties();
	
}

//애니메이션 플레이를 위한 프로퍼티 업데이트 함수
void UMHAnimInstance::UpdateProperties()
{
	SitOnGround = InstanceHost->SitOnGround;
	SitOnChair = InstanceHost->SitOnChair;
	StandingTalk = InstanceHost->StandingTalk;
	StandingClap = InstanceHost->StandingClap;
	Idle = InstanceHost->Idle;
	Walking = InstanceHost->Walking;
}

