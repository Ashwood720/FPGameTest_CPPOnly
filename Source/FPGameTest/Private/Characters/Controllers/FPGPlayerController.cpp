// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Controllers/FPGPlayerController.h"
#include "Characters/FPGBaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerInput.h"

void AFPGPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	CachedBaseCharacter = Cast<AFPGBaseCharacter>(InPawn);
}

void AFPGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &AFPGPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AFPGPlayerController::MoveRight);
	InputComponent->BindAxis("Turn", this, &AFPGPlayerController::Turn);
	InputComponent->BindAxis("LookUp", this, &AFPGPlayerController::LookUp);
	InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AFPGPlayerController::Jump);
	InputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &AFPGPlayerController::PlayerStartFire);
}

void AFPGPlayerController::MoveForward(float Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->MoveForward(Value);
	}
}

void AFPGPlayerController::MoveRight(float Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->MoveRight(Value);
	}
}

void AFPGPlayerController::Turn(float Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->Turn(Value);
	}
}

void AFPGPlayerController::LookUp(float Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->LookUp(Value);
	}
}

void AFPGPlayerController::Jump()
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->Jump();
	}
}

void AFPGPlayerController::PlayerStartFire()
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->StartFire();
	}
}