// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSGameState.h"
#include "FPSPlayerController.h"


// 所有客户端都会运行的函数
void AFPSGameState::MulticastOnMissionComplete_Implementation(APawn* InstigatorPawn, bool bMissionSuccess)
{
	// 对所有的Pawn进行循环
	//for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; It++)
	//{
	//	APawn* Pawn = It->Get();
	//	if (Pawn&&Pawn->IsLocallyControlled())
	//	{
	//		Pawn->DisableInput(nullptr);
	//	}
	//}

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
	{
		AFPSPlayerController* PC = Cast<AFPSPlayerController>(It->Get());
		if (PC&&PC->IsLocalController())
		{
			PC->OnMissionCompleted(InstigatorPawn, bMissionSuccess);

			// 禁止控制
			APawn* MyPawn = PC->GetPawn();
			if (MyPawn)
			{
				MyPawn->DisableInput(PC);
			}
		}
	}
}
