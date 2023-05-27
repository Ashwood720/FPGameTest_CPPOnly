// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/FPGBaseWeapon.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "AI/FPGAICharacter.h"
#include <FPGGameInstance.h>
#include <Kismet/GameplayStatics.h>

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

AFPGBaseWeapon::AFPGBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(GetRootComponent());
}

void AFPGBaseWeapon::Fire()
{
	UE_LOG(LogBaseWeapon, Display, TEXT("Fire"));

	FVector ViewLocation;
	FRotator ViewRotation;

	const auto Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	const auto Controller = Character->GetController<AController>();
	if (!Controller) return;

	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

	FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);

	FVector StartLine = SocketTransform.GetLocation();
	FVector ShotDirection = ViewRotation.Vector();
	FVector EndLine = StartLine + ShotDirection * 2000.0f;

	DrawDebugLine(GetWorld(), StartLine, EndLine, FColor::Red, false, 1.0f, 0, 1.0f);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	
	FHitResult HitResult;
	if(GetWorld()->LineTraceSingleByChannel(HitResult, StartLine, EndLine, ECollisionChannel::ECC_Visibility, CollisionParams))
	{
		DrawDebugLine(GetWorld(), StartLine, HitResult.ImpactPoint, FColor::Red, false, 1.0f, 0, 1.0f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 1.0f, 0, 1.0f);
		if (HitResult.GetActor()->IsA<AFPGAICharacter>())
		{
			UE_LOG(LogBaseWeapon, Display, TEXT("Bone: %s"), *HitResult.BoneName.ToString());

			const auto GameInstance = Cast<UFPGGameInstance>(GetGameInstance());
			float CurrentScore = GameInstance->GetCurrentScore();
			if (HitResult.BoneName == HeadBoneName)
			{
				UE_LOG(LogBaseWeapon, Display, TEXT("Hit: 50%"));
				UGameplayStatics::ApplyDamage(HitResult.GetActor(), 50.0f, Controller, nullptr, nullptr);
				GameInstance->SetCurrentScore(CurrentScore + 40);
				return;
			}

			UGameplayStatics::ApplyDamage(HitResult.GetActor(), 20.0f, Controller, nullptr, nullptr);
			GameInstance->SetCurrentScore(CurrentScore + 10);
			UE_LOG(LogBaseWeapon, Display, TEXT("Hit: 20%"));
		}
	}
	else
	{
		DrawDebugLine(GetWorld(), StartLine, EndLine, FColor::Red, false, 1.0f, 0, 1.0f);
	}
}