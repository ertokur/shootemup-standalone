// Erbol Tokur

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SEUWeaponComponent.generated.h"

class ASEUWeaponBase;
class USEUEquipFinishedAnimNotify;
struct FWeaponData;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTEMUP_API USEUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USEUWeaponComponent();

	void StartFire();
	void StopFire();
	void SwitchWeapon();
	void Reload();
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ASEUWeaponBase* GetEquippedWeapon() const { return CurrentWeapon; }

	UFUNCTION(BlueprintCallable)
	bool GetWeaponUIData(FWeaponUIData& UIData) const;

	UFUNCTION(BlueprintCallable)
	bool GetWeaponAmmoData(FAmmoData& AmmoData) const;

	bool TryToAddAmmo(int32 Amount);
	
protected:
	UPROPERTY(EditAnywhere, Category = Weapon)
	TArray<FWeaponData> StartingWeaponData;

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	UAnimMontage* EquipMontage;
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY()
	ASEUWeaponBase* CurrentWeapon = nullptr;

	int16 CurrentWeaponIndex = 0;

	bool bIsReloading = false;
	bool bIsEquipping = false;
	
	UPROPERTY()
	TArray<ASEUWeaponBase*> Weapons;

	void SpawnWeapons();
	void AttachWeaponToSocket(ASEUWeaponBase* Weapon, const FName& SocketName);
	void EquipWeapon(int16 WeaponIndex);
	void PlayAnimMontage(UAnimMontage* AnimMontage);
	void InitAnimNotifies();
	
	void OnEquipFinished(TObjectPtr<USkeletalMeshComponent> SkeletalMeshComp);
	void OnReloadFinished(TObjectPtr<USkeletalMeshComponent> SkeletalMeshComp);
	
	bool CanFire() const;
	bool CanEquip() const;
	bool CanReload() const;

	void OnEmptyClip();
	void OnChangeClip();

	

	FDelegateHandle ClipEmptyDelegateHandle;
};