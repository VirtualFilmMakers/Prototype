// Fill out your copyright notice in the Description page of Project Settings.


#include "D_ReplaySpectatorPawn.h"
#include "Engine/DemoNetDriver.h"
#include <Engine/World.h>
#include <Kismet/GameplayStatics.h>

AD_ReplaySpectatorPawn::AD_ReplaySpectatorPawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bShowMouseCursor = true;
	bShouldPerformFullTickWhenPaused = true;
	PrimaryActorTick.bTickEvenWhenPaused = true;

}


bool AD_ReplaySpectatorPawn::SetCurrentReplayPausedState(bool bDoPause) {
	AWorldSettings* WorldSettings = GetWorldSettings();

	// Set MotionBlur off and Anti Aliasing to FXAA in order to bypass the pause-bug of both
	static const auto CVarAA = IConsoleManager::Get().FindConsoleVariable(TEXT("r.DefaultFeature.AntiAliasing"));
	static const auto CVarMB = IConsoleManager::Get().FindConsoleVariable(TEXT("r.DefaultFeature.MotionBlur"));

	if (bDoPause)
	{
		PreviousAASetting = CVarAA->GetInt();
		PreviousMBSetting = CVarMB->GetInt();

		// Set MotionBlur to OFF, Anti-Aliasing to FXAA
		CVarAA->Set(1);
		CVarMB->Set(0);

		WorldSettings->SetPauserPlayerState(PlayerState);
		//WorldSettings->Pauser = PlayerState;
		return true;
	}
	// Rest MotionBlur and AA
	CVarAA->Set(PreviousAASetting);
	CVarMB->Set(PreviousMBSetting);

	WorldSettings->SetPauserPlayerState(NULL);
	return false;
}

int32 AD_ReplaySpectatorPawn::GetCurrentReplayTotalTimeInSeconds() const {
	if (GetWorld()) { if (GetWorld()->GetDemoNetDriver()) { return GetWorld()->GetDemoNetDriver()->GetDemoTotalTime(); } }

	return 0.f;
}

int32 AD_ReplaySpectatorPawn::GetCurrentReplayCurrentTimeInSeconds() const {
	if (GetWorld()) { if (GetWorld()->GetDemoNetDriver()) { return GetWorld()->GetDemoNetDriver()->GetDemoCurrentTime(); } }

	return 0.f;
}

void AD_ReplaySpectatorPawn::SetCurrentReplayTimeToSeconds(int32 Seconds) {
	if (GetWorld()) { if (GetWorld()->GetDemoNetDriver()) { GetWorld()->GetDemoNetDriver()->GotoTimeInSeconds(Seconds); } }
}

void AD_ReplaySpectatorPawn::SetCurrentReplayPlayRate(float PlayRate) {
	if (GetWorld()) { if (GetWorld()->GetDemoNetDriver()) { GetWorld()->GetWorldSettings()->DemoPlayTimeDilation = PlayRate; } }
}