// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include <FPGGameModeBase.h>
#include "FPGameHUD.generated.h"


class UUserWidget;

UCLASS()
class FPGAMETEST_API AFPGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	void GetGameOverWidget();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> PlayerWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> GameOverWidgetClass;

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TMap<EMatchState, UUserWidget*> GameWidgets;

	UPROPERTY()
	UUserWidget* CurrentWidget = nullptr;

	UPROPERTY()
	UUserWidget* CurrentGameOver = nullptr;

	void OnMatchStateChanged(EMatchState State);
};
