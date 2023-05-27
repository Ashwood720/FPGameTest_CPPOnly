// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/FPGBaseCharacter.h"
#include "FPGPlayerCharacter.generated.h"

class AFPGPlayerController;
class UCameraComponent;
class AController;
class UFPGWeaponComponent;
class USkeletalMeshComponent;

UCLASS(Blueprintable)
class FPGAMETEST_API AFPGPlayerCharacter : public AFPGBaseCharacter
{
	GENERATED_BODY()
	
public:
	AFPGPlayerCharacter();

	USkeletalMeshComponent* GetFirstPersonMesh() { return FirstPersonMeshComponent; }

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void OnDeath();

	virtual void MoveForward(float Value) override;
	virtual void MoveRight(float Value) override;
	virtual void Turn(float Value) override;
	virtual void LookUp(float Value) override;

	virtual void StartFire() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	USkeletalMeshComponent* FirstPersonMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	UCameraComponent* FirstPersonCameraComponent;

private:
	TWeakObjectPtr<AFPGPlayerController> PlayerController;
};
