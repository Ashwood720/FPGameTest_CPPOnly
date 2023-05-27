// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_FPGRandomLocation.generated.h"

UCLASS()
class FPGAMETEST_API UBTTaskNode_FPGRandomLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:
    UBTTaskNode_FPGRandomLocation();

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
        float Radius = 1000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
        FBlackboardKeySelector AimLocationKey;
};
