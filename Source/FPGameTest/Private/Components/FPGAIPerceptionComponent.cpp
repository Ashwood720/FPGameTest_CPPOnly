// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/FPGAIPerceptionComponent.h"
#include "AIController.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Damage.h"
#include <Characters/FPGPlayerCharacter.h>

AActor* UFPGAIPerceptionComponent::GetEnemy() const
{
	TArray<AActor*> PercieveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
	if (PercieveActors.Num() == 0)
	{
		GetCurrentlyPerceivedActors(UAISense_Damage::StaticClass(), PercieveActors);
		if (PercieveActors.Num() == 0) return nullptr;
	}

	const auto Controller = Cast<AAIController>(GetOwner());
	if (!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return nullptr;

	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;
	for (const auto PercieveActor : PercieveActors)
	{
		if (PercieveActor->IsA<AFPGPlayerCharacter>())
		{
			BestPawn = PercieveActor;
		}
	}
	return BestPawn;
}
