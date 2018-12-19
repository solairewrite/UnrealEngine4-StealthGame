// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPS_LaunchPad.generated.h"

class UBoxComponent;

UCLASS()
class FPSGAME_API AFPS_LaunchPad : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFPS_LaunchPad();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnyWhere, Category = "Components")
		UBoxComponent* OverlapComp;

	// 绑定Overlap事件
	UFUNCTION()
		void OverlapLaunchPad(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditInstanceOnly, Category = "LaunchPad") // 对单个实例进行编辑
		float LaunchStrength;

	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
		float LaunchPitchAngle;

	UPROPERTY(EditDefaultsOnly, Category = "LaunchPad") // 只能编辑默认的,所有实例都一样
		UParticleSystem* ActivateLaunchPadEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
		USoundBase* LaunchSound;

public:

};
