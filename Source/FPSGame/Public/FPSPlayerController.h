// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPSPlayerController.generated.h"

/**
 *
 */
UCLASS()
class FPSGAME_API AFPSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// 在UE中创建蓝图继承自这个类,蓝图中实现函数
	UFUNCTION(BlueprintImplementableEvent, Category = "PlayerController")
		void OnMissionCompleted(APawn* InstigatorPawn, bool bMissionSuccess);


};
