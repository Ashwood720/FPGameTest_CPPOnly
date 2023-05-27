// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Animations/FPGAnimInstance.h"
#include "AI/FPGAICharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UFPGAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	checkf(TryGetPawnOwner()->IsA<AFPGAICharacter>(), TEXT("UGCBaseCharacterAnimInstance::NativeBeginPlay() UGCBaseCharacterAnimInstance can be used only with AFPGBaseCharacter"));
	CachedBaseCharacter = StaticCast<AFPGAICharacter*>(TryGetPawnOwner());
}

void UFPGAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (!CachedBaseCharacter.IsValid())
	{
		return;
	}

	UCharacterMovementComponent* CharacterMovement = CachedBaseCharacter->GetCharacterMovement();
	Speed = CharacterMovement->Velocity.Size();
}