// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/FPGameHUD.h"
#include "Blueprint/UserWidget.h"
#include <FPGGameModeBase.h>

DEFINE_LOG_CATEGORY_STATIC(LogHUD, All, All);

void AFPGameHUD::GetGameOverWidget()
{
   /* const auto GameOverClass = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);
    if (GameOverClass)
    {
        GameOverClass->AddToViewport();
    }*/
}

/*void AFPGameHUD::BeginPlay()
{
	Super::BeginPlay();

	const auto PlayerWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerWidgetClass);
	if (PlayerWidget)
	{
		PlayerWidget->AddToViewport();
	}
}*/

void AFPGameHUD::BeginPlay()
{
    Super::BeginPlay();

    GameWidgets.Add(EMatchState::InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerWidgetClass));
    GameWidgets.Add(EMatchState::GameOver, CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass));

    for (auto GameWidgetPair : GameWidgets)
    {
        const auto GameWidget = GameWidgetPair.Value;
        if (!GameWidget) continue;

        GameWidget->AddToViewport();
        GameWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GetWorld())
    {
        const auto GameMode = Cast<AFPGGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &AFPGameHUD::OnMatchStateChanged);
        }
    }
}

void AFPGameHUD::OnMatchStateChanged(EMatchState State)
{
    UE_LOG(LogHUD, Display, TEXT("Match state: %s"), *UEnum::GetValueAsString(State));
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GameWidgets.Contains(State))
    {
        CurrentWidget = GameWidgets[State];
    }

    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Visible);
    }
}