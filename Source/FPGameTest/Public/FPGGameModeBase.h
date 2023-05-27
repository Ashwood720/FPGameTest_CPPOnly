// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPGGameModeBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchStateChangedSignature, EMatchState);

UENUM(BlueprintType)
enum class EMatchState : uint8
{
    WaitingToStart = 0,
    InProgress,
    GameOver
};

class AAIController;

UCLASS()
class FPGAMETEST_API AFPGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AFPGGameModeBase();

    FOnMatchStateChangedSignature OnMatchStateChanged;

    virtual void StartPlay() override;
    virtual void BeginPlay() override;
    virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

    void RespawnRequest(AController* Controller);

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<AAIController> AIControllerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<APawn> AIPawnClass;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    int32 NumNPC = 3;

    void SpawnBots(int Num);

    void StartRespawn(AController* Controller);
    void GameOver();
    void SetMatchState(EMatchState State);
    bool RestartGame();

private:
    EMatchState MatchState = EMatchState::WaitingToStart;
};
