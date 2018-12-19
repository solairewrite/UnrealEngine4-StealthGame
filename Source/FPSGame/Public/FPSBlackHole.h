// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSBlackHole.generated.h"

class USphereComponent;

UCLASS()
class FPSGAME_API AFPSBlackHole : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFPSBlackHole();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* MeshComp;

	// 内部的球,摧毁overlapping components
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* InnerShpereComponent;

	// 外部的球,把物体拉向中心
	UPROPERTY(VisibleAnywhere, Category = "Component")
		USphereComponent* OuterSphereComponent;

	//UFUNCTION标记, 用来 bind to overlap event
	UFUNCTION()
		void OverlapInnerShpere(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* OtherComp, int32 OthrBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void TestLog();

};
