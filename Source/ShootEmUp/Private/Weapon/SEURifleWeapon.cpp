// Erbol Tokur


#include "Weapon/SEURifleWeapon.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Weapon/Components/SEUWeaponFXComponent.h"


ASEURifleWeapon::ASEURifleWeapon()
{
	WeaponFXComponent = CreateDefaultSubobject<USEUWeaponFXComponent>(TEXT("WeaponFXComponent"));
}

void ASEURifleWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ASEURifleWeapon::MakeShot()
{
	Super::MakeShot();
	
	if (GetWorld() && WeaponOwner && CanFire() && !IsAmmoEmpty())
	{
		FVector ViewLocation;
		FRotator ViewRotation;
		Cast<APlayerController>(WeaponOwner->Controller)->GetPlayerViewPoint(ViewLocation, ViewRotation);
			
		const FTransform SocketTransform = SkeletalMesh->GetSocketTransform("SOCKET_Muzzle");

		const FVector TraceStart = ViewLocation;
		const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), FMath::DegreesToRadians(SpreadAngle));
		const FVector TraceEnd = TraceStart + ShootDirection * TraceDistance;

		FCollisionQueryParams Params;
		Params.bReturnPhysicalMaterial = true;
		
#if !(UE_BUILD_TEST || UE_BUILD_SHIPPING)
		Params.bDebugQuery = true;
#endif

		Params.AddIgnoredActor(WeaponOwner);
		
		FHitResult HitResult;
		if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, Params))
		{
			//DrawDebugLine(GetWorld(), SocketTransform.GetLocation(),  HitResult.ImpactPoint, FColor::Green, false, 0.5f, 0, 1.0f);
			//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 16, FColor::Green, false, 0.5, 0, 1.0f);
			WeaponFXComponent->PlayImpactFX(HitResult);
			MakeDamage(HitResult);
		}
		else
		{
			//DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), TraceEnd, FColor::Red, false, 0.5f, 0, 1.0f);
		}

		DecreaseAmmo();
	}
}

void ASEURifleWeapon::MakeDamage(const FHitResult& Hit)
{
	if (WeaponOwner && WeaponOwner->Controller)
	{
		UGameplayStatics::ApplyDamage(Hit.GetActor(), BaseDamage, WeaponOwner->Controller, this, UDamageType::StaticClass());
	}
}