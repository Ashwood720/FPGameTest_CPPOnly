// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FPGGameOverWidget.generated.h"

class UButton;

UCLASS()
class FPGAMETEST_API UFPGGameOverWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
    UPROPERTY(meta = (BindWidget))
    UButton* RestartButton;

    UPROPERTY(meta = (BindWidget))
    UButton* QuitGameButton;

    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetBestScores() const;

    virtual void NativeOnInitialized() override;

private:
    UFUNCTION()
        void OnRestart();

    UFUNCTION()
        void OnQuitGame();
};