// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPGBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class FPGAMETEST_API AFPGBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPGBaseWeapon();

	void Fire();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	USkeletalMeshComponent* WeaponMesh;

private:
	FName MuzzleSocketName = "Muzzle";
	FName HeadBoneName = "head";
};
