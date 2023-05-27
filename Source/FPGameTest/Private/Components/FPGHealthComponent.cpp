// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/FPGHealthComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

UFPGHealthComponent::UFPGHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UFPGHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	check(MaxHealth > 0);

	SetHealth(MaxHealth);
	UE_LOG(LogHealthComponent, Display, TEXT("Health: %f"), Health);
	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UFPGHealthComponent::OnTakeAnyDamage);
	}
}


void UFPGHealthComponent::OnTakeAnyDamage(
	AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || IsDead() || !GetWorld()) return;

	SetHealth(Health - Damage);

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
}

void UFPGHealthComponent::SetHealth(float NewHealth)
{
	float NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	float HealthDelta = NextHealth - Health;

	Health = NextHealth;
}