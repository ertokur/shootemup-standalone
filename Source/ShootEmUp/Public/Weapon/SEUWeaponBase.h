// Erbol Tokur

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/SEUCoreTypes.h"
#include "SEUWeaponBase.generated.h"

DECLARE_MULTICAST_DELEGATE(FClipEmptySignature);


UCLASS(NotBlueprintable)
class SHOOTEMUP_API ASEUWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	ASEUWeaponBase();
	
	virtual void StartFire();
	virtual void StopFire();

	void DecreaseAmmo();
	bool IsAmmoEmpty() const;
	bool IsClipEmpty() const;
	bool CanReload() const;
	void Reload();
	bool TryToAddAmmo(int32 Amount);

	FClipEmptySignature OnClipEmpty;

	inline FWeaponUIData GetUIData() const { return UIData; }

	inline FAmmoData GetAmmoData() const { return CurrentAmmoData; }
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Settings)
	FAmmoData DefaultAmmoData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Settings)
	FWeaponUIData UIData;
	
	virtual void BeginPlay() override;

	virtual void MakeShot();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Settings, meta = (ClampMin = 0))
	float FireRate = 10.f;

	UPROPERTY()
	ACharacter* WeaponOwner = nullptr;

	bool CanFire() const;
	
	void LogAmmo();
	
private:
	FTimerHandle FireTimerHandle;
	FAmmoData CurrentAmmoData;
	bool bIsFiring = false;
};