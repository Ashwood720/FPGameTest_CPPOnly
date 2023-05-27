// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPGBaseCharacter.generated.h"

class UFPGHealthComponent;
class UFPGWeaponComponent;

UCLASS(Abstract, NotBlueprintable)
class FPGAMETEST_API AFPGBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFPGBaseCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void MoveForward(float Value) {};
	virtual void MoveRight(float Value) {};
	virtual void Turn(float Value) {};
	virtual void LookUp(float Value) {};

	virtual void StartFire() {};

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	class UTextRenderComponent* TextHealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UFPGHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	UFPGWeaponComponent* WeaponComponent;
};
