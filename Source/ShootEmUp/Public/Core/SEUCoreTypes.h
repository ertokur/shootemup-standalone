// Erbol Tokur

#pragma once

#include "CoreMinimal.h"
#include "SEUCoreTypes.generated.h"

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	TSubclassOf<class ASEUWeaponBase> WeaponClass = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	TObjectPtr<UAnimMontage> ReloadAnimMontage = nullptr;
};

USTRUCT(BlueprintType)
struct FWeaponUIData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
	TSoftObjectPtr<UTexture2D> WeaponTexture = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
	TSoftObjectPtr<UTexture2D> CrosshairTexture = nullptr;
};

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	int32 Bullets = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon, meta = (EditCondition = "!bIsInfinite", EditConditionHides))
	int32 Clips = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	bool bIsInfinite = false;
};