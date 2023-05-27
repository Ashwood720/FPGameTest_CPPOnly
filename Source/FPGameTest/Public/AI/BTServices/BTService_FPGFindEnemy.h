// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_FPGFindEnemy.generated.h"

UCLASS()
class FPGAMETEST_API UBTService_FPGFindEnemy : public UBTService
{
	GENERATED_BODY()

public:
    UBTService_FPGFindEnemy();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
        FBlackboardKeySelector EnemyActorKey;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
