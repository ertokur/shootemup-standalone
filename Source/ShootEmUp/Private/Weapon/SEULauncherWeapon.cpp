// Erbol Tokur


#include "Weapon/SEULauncherWeapon.h"

#include "Components/SphereComponent.h"
#include "Weapon/SEUProjectile.h"
#include "Kismet/GameplayStatics.h"

void ASEULauncherWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ASEULauncherWeapon::MakeShot()
{
	Super::MakeShot();
	
	if (!GetWorld() || !ProjectileClass || !CanFire() || IsAmmoEmpty())
		return;
	
	const FTransform SpawnTransform(SkeletalMesh->GetSocketRotation("SOCKET_Muzzle"), SkeletalMesh->GetSocketLocation("SOCKET_Muzzle"));
	auto Projectile = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), ProjectileClass, SpawnTransform);

	if (Projectile)
	{
		Cast<ASEUProjectile>(Projectile)->CollisionComp->IgnoreActorWhenMoving(this, true);
		Cast<ASEUProjectile>(Projectile)->CollisionComp->IgnoreActorWhenMoving(GetOwner(), true);
		UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);
	}

	DecreaseAmmo();
}