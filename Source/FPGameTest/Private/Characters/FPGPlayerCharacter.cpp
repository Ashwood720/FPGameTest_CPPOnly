// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/FPGPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"

#include "Components/FPGHealthComponent.h"
#include <FPGGameModeBase.h>
#include "Kismet/GameplayStatics.h"
#include <FPGGameInstance.h>
#include "Components/FPGWeaponComponent.h"
#include "Weapon/FPGBaseWeapon.h"
#include <UI/FPGameHUD.h>
#include "Blueprint/UserWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogPlayerCharacter, All, All);

AFPGPlayerCharacter::AFPGPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetRootComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 45.0f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	FirstPersonMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
    FirstPersonMeshComponent->SetupAttachment(FirstPersonCameraComponent);
    FirstPersonMeshComponent->SetRelativeLocation(FVector(-20.0f, 0.0f, -155.0f));

	bUseControllerRotationYaw = true;
}

void AFPGPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(HealthComponent);
	check(TextHealthComponent);

	HealthComponent->OnDeath.AddUObject(this, &AFPGPlayerCharacter::OnDeath);
}

void AFPGPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFPGPlayerCharacter::MoveForward(float Value)
{
	if (Value == 0.0f) return;
	AddMovementInput(GetActorForwardVector(), Value);
}

void AFPGPlayerCharacter::MoveRight(float Value)
{
	if (Value == 0.0f) return;
	AddMovementInput(GetActorRightVector(), Value);
}

void AFPGPlayerCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AFPGPlayerCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AFPGPlayerCharacter::StartFire()
{
	WeaponComponent->Fire();
}

void AFPGPlayerCharacter::OnDeath()
{
	const auto GameInstance = Cast<UFPGGameInstance>(GetGameInstance());
	
	GetWorld()->DestroyActor(this);
	GetWorld()->DestroyActor(WeaponComponent->GetWeapon());

	float CurrentLives = GameInstance->GetLives();
	CurrentLives--;
	GameInstance->SetLives(CurrentLives);
	const auto GameMode = Cast<AFPGGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;
	if (GameInstance->GetLives() != 0)
	{
		UE_LOG(LogPlayerCharacter, Display, TEXT("Restart"));

		UGameplayStatics::GetPlayerController(GetWorld(), 0);

		GameMode->RestartPlayerAtPlayerStart(UGameplayStatics::GetPlayerController(GetWorld(), 0), UGameplayStatics::GetPlayerController(GetWorld(), 0));
		return;
	}
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
	GameMode->GameOver();
}