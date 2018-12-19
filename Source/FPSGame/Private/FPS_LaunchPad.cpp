// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_LaunchPad.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AFPS_LaunchPad::AFPS_LaunchPad()
{
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetBoxExtent(FVector(75, 75, 50));
	RootComponent = OverlapComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);

	// 绑定Overlap事件
	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFPS_LaunchPad::OverlapLaunchPad);

	LaunchStrength = 1500;
	LaunchPitchAngle = 35.0f;
}

void AFPS_LaunchPad::OverlapLaunchPad(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// 设置发射速度
	FRotator LaunchDirection = GetActorRotation();
	LaunchDirection.Pitch = LaunchPitchAngle;
	FVector LaunchVelocity = LaunchDirection.Vector()*LaunchStrength;

	ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
	if (OtherCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("有Character进入发射板"));

		// 发射主角,无视原有速度
		OtherCharacter->LaunchCharacter(LaunchVelocity, true, true);

		// 生成粒子效果,播放声音
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ActivateLaunchPadEffect, GetActorLocation());
		UGameplayStatics::PlaySound2D(this, LaunchSound);
	}
	// 检查出了玩家外,模拟物理效果的物体,发射
	else if (OtherComp&&OtherComp->IsSimulatingPhysics())
	{
		// NAME_None: 骨骼名称,true: 是否以速度代替力(忽视质量)
		OtherComp->AddImpulse(LaunchVelocity, NAME_None, true);

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ActivateLaunchPadEffect, GetActorLocation());
	}
}



