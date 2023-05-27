// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FPGPlayerWidget.generated.h"

UCLASS()
class FPGAMETEST_API UFPGPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetHealthPercent() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetLives() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetScores() const;
};
