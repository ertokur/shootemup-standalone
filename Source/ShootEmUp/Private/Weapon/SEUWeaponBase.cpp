// Erbol Tokur

#include "Weapon/SEUWeaponBase.h"
#include "Core/SEUCharacterBase.h"
#include "GameFramework/Character.h"


ASEUWeaponBase::ASEUWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	RootComponent = SkeletalMesh;
}

void ASEUWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	check(SkeletalMesh);

	WeaponOwner = Cast<ACharacter>(GetOwner());
	CurrentAmmoData = DefaultAmmoData;
}

void ASEUWeaponBase::StartFire()
{
	bIsFiring = true;
	
	if (!GetWorld())
		return;

	if (!GetWorld()->GetTimerManager().IsTimerActive(FireTimerHandle))
	{
		GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &ASEUWeaponBase::MakeShot, 1/FireRate, true, 0);
	}
}

void ASEUWeaponBase::StopFire()
{
	bIsFiring = false;
}

void ASEUWeaponBase::MakeShot()
{
	if (!CanFire() || IsAmmoEmpty())
	{
		GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
	}
}

bool ASEUWeaponBase::CanFire() const
{
	return bIsFiring && !Cast<ASEUCharacterBase>(WeaponOwner)->IsSprint();
}

void ASEUWeaponBase::DecreaseAmmo()
{
	if (CurrentAmmoData.Bullets == 0)
	{
		return;
	}
	
	CurrentAmmoData.Bullets--;

	if (IsClipEmpty() && !IsAmmoEmpty())
	{
		OnClipEmpty.Broadcast();
	}
}

bool ASEUWeaponBase::IsAmmoEmpty() const
{
	return !CurrentAmmoData.bIsInfinite && CurrentAmmoData.Clips == 0 && IsClipEmpty();
}

bool ASEUWeaponBase::IsClipEmpty() const
{
	return CurrentAmmoData.Bullets == 0;
}

bool ASEUWeaponBase::CanReload() const
{
	return CurrentAmmoData.Bullets < DefaultAmmoData.Bullets && CurrentAmmoData.Clips > 0;
}

void ASEUWeaponBase::Reload()
{
	if (!CurrentAmmoData.bIsInfinite)
	{
		if (CurrentAmmoData.Clips == 0)
		{
			return;
		}
		
		CurrentAmmoData.Clips--;
	}
	
	CurrentAmmoData.Bullets = DefaultAmmoData.Bullets;
}

bool ASEUWeaponBase::TryToAddAmmo(int32 Amount)
{
	if (Amount > 0)
	{
		if (!DefaultAmmoData.bIsInfinite && (CurrentAmmoData.Clips < DefaultAmmoData.Clips))
		{
			CurrentAmmoData.Clips = FMath::Clamp(CurrentAmmoData.Clips + Amount, 0, DefaultAmmoData.Clips);
			return true;
		}
	}
	
	return false;
}

void ASEUWeaponBase::LogAmmo()
{
	FString AmmoStr = "Ammo: " + FString::FromInt(CurrentAmmoData.Bullets) + " / ";
	AmmoStr += CurrentAmmoData.bIsInfinite ? "Infinite" : FString::FromInt(CurrentAmmoData.Clips);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *AmmoStr);
}