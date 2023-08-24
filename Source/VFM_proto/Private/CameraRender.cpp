// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraRender.h"
#include <Engine/TextureRenderTarget2D.h>
#include <HighResScreenshot.h>

// Sets default values
ACameraRender::ACameraRender()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraRender::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraRender::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACameraRender::SaveRenderTargetToDisk(UTextureRenderTarget2D* InRenderTarget, FString Filename)
{
    FTextureRenderTargetResource* RTResource = InRenderTarget->GameThread_GetRenderTargetResource();

    FReadSurfaceDataFlags ReadPixelFlags(RCM_UNorm);
    ReadPixelFlags.SetLinearToGamma(true);

    TArray<FColor> OutBMP;
    RTResource->ReadPixels(OutBMP, ReadPixelFlags);

    for (FColor& color : OutBMP)
    {
        color.A = 255;
    }


    FIntRect SourceRect;

    FIntPoint DestSize(InRenderTarget->GetSurfaceWidth(), InRenderTarget->GetSurfaceHeight());


    FString ResultPath;
    FHighResScreenshotConfig& HighResScreenshotConfig = GetHighResScreenshotConfig();
    HighResScreenshotConfig.SaveImage(Filename, OutBMP, DestSize, &ResultPath);
}

