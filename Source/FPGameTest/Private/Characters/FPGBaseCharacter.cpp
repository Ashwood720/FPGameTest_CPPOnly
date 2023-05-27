// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/FPGBaseCharacter.h"
#include "Components/FPGHealthComponent.h"
#include <Components/FPGWeaponComponent.h>
#include "Components/TextRenderComponent.h"

AFPGBaseCharacter::AFPGBaseCharacter()
{
	HealthComponent = CreateDefaultSubobject<UFPGHealthComponent>("HealthComponent");
	WeaponComponent = CreateDefaultSubobject<UFPGWeaponComponent>("WeaponComponent");

	TextHealthComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("HealthText"));
	TextHealthComponent->SetupAttachment(GetRootComponent());
}

void AFPGBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AFPGBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float Health = HealthComponent->GetHealth();
	TextHealthComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}