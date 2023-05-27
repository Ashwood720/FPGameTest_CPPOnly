// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/FPGAICharacter.h"
#include "AI/Controllers/FPGAIController.h"
#include "BrainComponent.h"
#include "Components/FPGHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include <FPGGameModeBase.h>
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include <Kismet/GameplayStatics.h>
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include <Characters/FPGPlayerCharacter.h>

DEFINE_LOG_CATEGORY_STATIC(LogAICharacter, All, All);

AFPGAICharacter::AFPGAICharacter()
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = AFPGAIController::StaticClass();

    CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
    CollisionComponent->InitCapsuleSize(35.0f, 90.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    CollisionComponent->SetupAttachment(GetRootComponent());
}

void AFPGAICharacter::BeginPlay()
{
    Super::BeginPlay();
    check(HealthComponent);
    check(TextHealthComponent);
    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AFPGAICharacter::OnCollisionOverlap);
    HealthComponent->OnDeath.AddUObject(this, &AFPGAICharacter::OnDeath);
}

void AFPGAICharacter::OnCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor->IsA<AFPGPlayerCharacter>())
    {
        UGameplayStatics::ApplyDamage(OtherActor, 25.0f, Controller, nullptr, nullptr);
    }
}

void AFPGAICharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void AFPGAICharacter::OnDeath()
{
	GetWorld()->DestroyActor(this);
	const auto GameMode = Cast<AFPGGameModeBase>(GetWorld()->GetAuthGameMode());
    GameMode->SpawnBots(1);
}