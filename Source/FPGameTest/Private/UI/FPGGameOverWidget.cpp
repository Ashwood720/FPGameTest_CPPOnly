// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FPGGameOverWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Components/Button.h"
#include <Kismet/GameplayStatics.h>
#include <FPGGameInstance.h>

int32 UFPGGameOverWidget::GetBestScores() const
{
    const auto GameInstance = Cast<UFPGGameInstance>(GetGameInstance());
    int32 CurrentScore = GameInstance->GetCurrentScore();
    int32 BestScore = GameInstance->GetBestScore();

    if(CurrentScore > BestScore)
    {
        GameInstance->SetBestScore(CurrentScore);
    }
    return GameInstance->GetBestScore();
}

void UFPGGameOverWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (RestartButton)
    {
        RestartButton->OnClicked.AddDynamic(this, &UFPGGameOverWidget::OnRestart);
    }

    if (QuitGameButton)
    {
        QuitGameButton->OnClicked.AddDynamic(this, &UFPGGameOverWidget::OnQuitGame);
    }
}

void UFPGGameOverWidget::OnRestart()
{
    const FName Level = "FirstPersonMap";
    UGameplayStatics::OpenLevel(this, Level);
    const auto GameInstance = Cast<UFPGGameInstance>(GetGameInstance());
    if (GameInstance)
    {
        GameInstance->SetCurrentScore(0);
        GameInstance->SetLives(3);
    }
}

void UFPGGameOverWidget::OnQuitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
