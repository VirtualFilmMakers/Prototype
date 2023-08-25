// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraRender.h"
//#include <Engine/TextureRenderTarget2D.h>
//#include <HighResScreenshot.h>
//#include <GameFramework/PlayerController.h>
//#include <Kismet/KismetRenderingLibrary.h>
//#include <ImageUtils.h>
//#include <LevelSequence/Public/LevelSequenceActor.h>
//#include <LevelSequence/Public/LevelSequence.h>

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
	
	//// 
	//FString FullPath = FString::Printf(TEXT("%s%s"), *FPaths::ProjectDir(), TEXT("testOutImage.png"));
	//FArchive* ArWriter = IFileManager::Get().CreateFileWriter(*FullPath); // 경로에 파일을 만든다
	//FImageUtils::ExportRenderTarget2DAsPNG(renderTex, *ArWriter);
	

	//class ALevelSequenceActor;
	//class ULevelSequence;

	//ALevelSequenceActor* testSequence = NewObject<ALevelSequenceActor>(this, ALevelSequenceActor::StaticClass());
	//ULevelSequence* seq = new ULevelSequence();
	/*testSequence->*/

	
}

// Called every frame
void ACameraRender::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//void ACameraRender::RenderFromRenderTarget(UTextureRenderTarget2D* inRenderTex)
//{
//	int32 width = inRenderTex->SizeX;
//	int32 height = inRenderTex->SizeY;
//
//	TArray<FColor> imgArr;
//	UKismetRenderingLibrary::ReadRenderTarget(GetWorld(), inRenderTex, imgArr);
//
//	TArray<uint8> imgByte;
//	FImageUtils::CompressImageArray(width, height, imgArr, imgByte);
//	FFileHelper::SaveArrayToFile(imgByte, *FString("D:/renderTest"));
//}

//
//void ACameraRender::SaveRenderTargetToDisk(UTextureRenderTarget2D* InRenderTarget, FString Filename)
//{
//    FTextureRenderTargetResource* RTResource = InRenderTarget->GameThread_GetRenderTargetResource();
//
//    FReadSurfaceDataFlags ReadPixelFlags(RCM_UNorm);
//    ReadPixelFlags.SetLinearToGamma(true);
//
//    TArray<FColor> OutBMP;
//    RTResource->ReadPixels(OutBMP, ReadPixelFlags);
//
//    for (FColor& color : OutBMP)
//    {
//        color.A = 255;
//    }
//
//
//    FIntRect SourceRect;
//
//    FIntPoint DestSize(InRenderTarget->GetSurfaceWidth(), InRenderTarget->GetSurfaceHeight());
//
//
//    FString ResultPath;
//    FHighResScreenshotConfig& HighResScreenshotConfig = GetHighResScreenshotConfig();
//    HighResScreenshotConfig.SaveImage(Filename, OutBMP, DestSize, &ResultPath);
//   
//}



