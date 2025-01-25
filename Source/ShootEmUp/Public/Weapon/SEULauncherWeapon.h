// Erbol Tokur

#pragma once

#include "CoreMinimal.h"
#include "SEUWeaponBase.h"
#include "SEULauncherWeapon.generated.h"

class ASEUProjectile;

UCLASS(Blueprintable)
class SHOOTEMUP_API ASEULauncherWeapon : public ASEUWeaponBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void MakeShot() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<ASEUProjectile> ProjectileClass;
};