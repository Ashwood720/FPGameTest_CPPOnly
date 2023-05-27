// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTServices/BTService_FPGFindEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Components/FPGAIPerceptionComponent.h"

UBTService_FPGFindEnemy::UBTService_FPGFindEnemy()
{
    NodeName = "Find Enemy";
}

void UBTService_FPGFindEnemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    if (const auto Blackboard = OwnerComp.GetBlackboardComponent())
    {
        const auto Controller = OwnerComp.GetAIOwner();
        const auto PerceptionComponent = Controller->GetComponentByClass<UFPGAIPerceptionComponent>();
        if (PerceptionComponent)
        {
            Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetEnemy());
        }
    }
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}