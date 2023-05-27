// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Controllers/FPGAIController.h"
#include <AI/FPGAICharacter.h>
#include <Components/FPGAIPerceptionComponent.h>
#include "BehaviorTree/BlackboardComponent.h"

AFPGAIController::AFPGAIController()
{
    FPGAIPerceptionComponent = CreateDefaultSubobject<UFPGAIPerceptionComponent>("FPGPerceptionComponent");
    SetPerceptionComponent(*FPGAIPerceptionComponent);
}

void AFPGAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    const auto NPCCharacter = Cast<AFPGAICharacter>(InPawn);
    if (NPCCharacter)
    {
        RunBehaviorTree(NPCCharacter->BehaviorTreeAsset);
    }
}

void AFPGAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

AActor* AFPGAIController::GetFocusOnActor() const
{
    if (!GetBlackboardComponent()) return nullptr;
    return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}