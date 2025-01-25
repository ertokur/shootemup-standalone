// Erbol Tokur

#pragma once

#include "CoreMinimal.h"
#include "SEUWeaponBase.h"
#include "SEURifleWeapon.generated.h"

UCLASS(Blueprintable)
class SHOOTEMUP_API ASEURifleWeapon : public ASEUWeaponBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void MakeShot() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Settings)
	float TraceDistance = 10000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Settings, meta = (ClampMin = 1))
	float SpreadAngle = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Settings)
	float BaseDamage = 10.f;
	
private:

	void MakeDamage(const FHitResult& Hit);
};