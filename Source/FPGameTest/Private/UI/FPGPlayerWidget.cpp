// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FPGPlayerWidget.h"
#include <Components/FPGHealthComponent.h>
#include "Characters/FPGBaseCharacter.h"
#include <FPGGameInstance.h>

float UFPGPlayerWidget::GetHealthPercent() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) return 0.0f;
	const auto Component = Player->GetComponentByClass(UFPGHealthComponent::StaticClass());
	const auto HealthComponent = Cast<UFPGHealthComponent>(Component);

	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

int32 UFPGPlayerWidget::GetLives() const
{
	const auto GameInstance = Cast<UFPGGameInstance>(GetGameInstance());
	if (!GameInstance)
	{
		return 0;
	}
	return GameInstance->GetLives();
}

int32 UFPGPlayerWidget::GetScores() const
{
	const auto GameInstance = Cast<UFPGGameInstance>(GetGameInstance());
	if (!GameInstance)
	{
		return 0;
	}
	return GameInstance->GetCurrentScore();
}