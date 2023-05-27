// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FPGGameInstance.generated.h"

UCLASS()
class FPGAMETEST_API UFPGGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	int32 GetLives() { return Lives; }
	int32 GetCurrentScore() { return CurrentScore; }
	int32 GetBestScore() { return BestScore; }

	void SetLives(int32 NewLives) { Lives = NewLives; }
	void SetCurrentScore(int32 NewCurrentScore) { CurrentScore = NewCurrentScore; }
	void SetBestScore(int32 NewBestScore) { BestScore = NewBestScore; }

private:
	int32 Lives = 3;
	int32 CurrentScore = 0;
	int32 BestScore = 0;
};
