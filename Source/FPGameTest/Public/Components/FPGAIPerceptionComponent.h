// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "FPGAIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class FPGAMETEST_API UFPGAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
	
public:
	AActor* GetEnemy() const;
};
