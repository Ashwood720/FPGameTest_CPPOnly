// Fill out your copyright notice in the Description page of Project Settings.


#include "FPGGameModeBase.h"
#include "Characters/FPGPlayerCharacter.h"
#include "Characters/Controllers/FPGPlayerController.h"
#include "AIController.h"
#include "EngineUtils.h"
#include "UI/FPGameHUD.h"
#include <GameFramework/GameMode.h>
#include "Blueprint/UserWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogTenGameModeBase, All, All);

AFPGGameModeBase::AFPGGameModeBase()
{
	DefaultPawnClass = AFPGBaseCharacter::StaticClass();
	PlayerControllerClass = AFPGPlayerController::StaticClass();
	HUDClass = AFPGameHUD::StaticClass();
}

void AFPGGameModeBase::StartPlay()
{
	Super::StartPlay();

	SpawnBots(NumNPC);

	SetMatchState(EMatchState::InProgress);
}

void AFPGGameModeBase::BeginPlay()
{
	Super::BeginPlay();


}

UClass* AFPGGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<AAIController>())
	{
		return AIPawnClass;
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void AFPGGameModeBase::RespawnRequest(AController* Controller)
{
	if (Controller && Controller->GetPawn()) 
	{
		Controller->GetPawn()->Reset();
	}
	RestartPlayer(Controller);
}

void AFPGGameModeBase::SpawnBots(int Num)
{
	if (!GetWorld()) return;

	for (int32 i = 0; i < Num; ++i)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto NPS_AIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
		RestartPlayer(NPS_AIController);
	}
}

void AFPGGameModeBase::StartRespawn(AController* Controller)
{
	if (Controller && Controller->GetPawn())
	{
		Controller->GetPawn()->Reset();
	}
	RestartPlayer(Controller);
}

void AFPGGameModeBase::GameOver()
{
	for (auto Pawn : TActorRange<APawn>(GetWorld()))
	{
		if (Pawn)
		{
			Pawn->TurnOff();
			Pawn->DisableInput(nullptr);
		}
	}

	SetMatchState(EMatchState::GameOver);
}

void AFPGGameModeBase::SetMatchState(EMatchState State)
{
	if (MatchState == State) return;

	MatchState = State;
	OnMatchStateChanged.Broadcast(MatchState);
}

bool AFPGGameModeBase::RestartGame()
{
	const auto PauseCleared = Super::ClearPause();
	if (PauseCleared)
	{
		SetMatchState(EMatchState::InProgress);
	}
	return PauseCleared;
}