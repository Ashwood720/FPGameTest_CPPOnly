// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/FPGBaseCharacter.h"
#include "FPGAICharacter.generated.h"

class UBehaviorTree;
class UCapsuleComponent;

UCLASS(Blueprintable)
class FPGAMETEST_API AFPGAICharacter : public AFPGBaseCharacter
{
	GENERATED_BODY()
	
public:
	AFPGAICharacter();

	UPROPERTY(VisibleAnywhere, Category = "Pickup")
	UCapsuleComponent* CollisionComponent;

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	void OnDeath();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;

private:
	UFUNCTION()
	void OnCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
