// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FPGWeaponComponent.generated.h"

class AFPGBaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPGAMETEST_API UFPGWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFPGWeaponComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	AFPGBaseWeapon* GetWeapon() const {return CurrentWeapon;}
	void Fire();

	void SpawnWeapon();
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AFPGBaseWeapon> WeaponClass;

private:
	AFPGBaseWeapon* CurrentWeapon;
	FName WeaponArmorySocketName = "GripPoint";
};
