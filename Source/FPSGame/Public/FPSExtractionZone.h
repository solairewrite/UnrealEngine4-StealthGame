// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSExtractionZone.generated.h"

class UBoxComponent;

UCLASS()
class FPSGAME_API AFPSExtractionZone : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFPSExtractionZone();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UBoxComponent* OverlapComp;

	// 长方体边框显示
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UDecalComponent* DecalComp;

	// OnComponentBeginOverlap 点击跳转可以看到参数
	UFUNCTION()
		void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// 播放声音
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
		USoundBase* ObjectiveMissingSound;

};
