// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "O_CameraBase.h"
#include "O_Camera_Tripod.generated.h"

/**
 * 
 */
UCLASS()
class VFM_PROTO_API AO_Camera_Tripod : public AO_CameraBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AO_Camera_Tripod();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;




	// 카메라 상단
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	class USceneComponent* compTirpodUp;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	class UStaticMeshComponent* ACamera;
	

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	class UStaticMeshComponent* Tripod2_Cylinder_002;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	class UStaticMeshComponent* Tripod2_Cylinder_004;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	class UStaticMeshComponent* Tripod2_Cylinder_005;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	class UStaticMeshComponent* Tripod2_Cylinder_006;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	class UStaticMeshComponent* Tripod2_Cylinder_008;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	class UStaticMeshComponent* Tripod2_Gewinde;


	// 카메라 하단부 (고정)
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	class USceneComponent* compTirpodDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class UStaticMeshComponent* Tripod2_Cylinder;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	class UStaticMeshComponent* Tripod2_Cylinder_001;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	class UStaticMeshComponent* Tripod2_Beine;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	class UStaticMeshComponent* Tripod2_Beine_001;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	class UStaticMeshComponent* Tripod2_Beine_002;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	class UStaticMeshComponent* Tripod2_Cone;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	class UStaticMeshComponent* Tripod2_Cone_001;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	class UStaticMeshComponent* Tripod2_Cone_002;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	class UStaticMeshComponent* Tripod2_Griffel;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	class UStaticMeshComponent* Tripod2_Griffel_001;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	class UStaticMeshComponent* Tripod2_Griffel_002;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	class UStaticMeshComponent* Tripod2_Griffel_003;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	class UStaticMeshComponent* Tripod2_Griffel_004;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	class UStaticMeshComponent* Tripod2_Griffel_005;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	class UStaticMeshComponent* Tripod2_Griffel_006;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	class UStaticMeshComponent* Tripod2_Griffel_007;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	class UStaticMeshComponent* Tripod2_Griffel_008;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	class UStaticMeshComponent* Tripod222_Cylinder_002;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	class UStaticMeshComponent* Tripod222_Object001;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	class UStaticMeshComponent* Tripod222_Object002;






	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Enhanced Input")
	class UInputMappingContext* TripodInputMapping;


	
};
