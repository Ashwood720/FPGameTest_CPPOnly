// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/FPGWeaponComponent.h"
#include <Characters/FPGPlayerCharacter.h>
#include <Weapon/FPGBaseWeapon.h>

UFPGWeaponComponent::UFPGWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UFPGWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

    SpawnWeapon();
}

void UFPGWeaponComponent::Fire()
{
    CurrentWeapon->Fire();
}

void UFPGWeaponComponent::SpawnWeapon()
{
    if (!WeaponClass) return;
    const auto Character = Cast<AFPGPlayerCharacter>(GetOwner());
    if (!Character || !GetWorld()) return;
    const auto SpawnWeapon = GetWorld()->SpawnActor<AFPGBaseWeapon>(WeaponClass);

    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    SpawnWeapon->AttachToComponent(Character->GetFirstPersonMesh(), AttachmentRules, WeaponArmorySocketName);
    CurrentWeapon = SpawnWeapon;
    CurrentWeapon->SetOwner(GetOwner());
    //AttachWeaponToSocket(SpawnWeapon, Character->GetMesh(), WeaponArmorySocketName);
}