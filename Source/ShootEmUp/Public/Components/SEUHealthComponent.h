// Erbol Tokur

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SEUHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOwnerTakeAnyDamageSignature, AActor*, DamagedActor, float, Damage, const UDamageType*, DamageType, AController*, InstigatedBy, AActor*, DamageCauser);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHealthChangedSignature, const float, OldHealth, const float, NewHealth);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTEMUP_API USEUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USEUHealthComponent();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Health")
	FORCEINLINE float GetHealth() const { return Health;}

	UFUNCTION(BlueprintCallable, Category="Health")
	void SetHealth(const float NewHealth);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Health")
	FORCEINLINE bool IsDead() const { return FMath::IsNearlyEqual(Health, 0.0f); }
	
	UPROPERTY(BlueprintAssignable, Category="Damage")
	FOwnerTakeAnyDamageSignature OnOwnerTakeDamage;

	UPROPERTY(BlueprintAssignable, Category="Damage")
	FDeathSignature OnDeath;

	UPROPERTY(BlueprintAssignable, Category="Damage")
	FHealthChangedSignature OnHealthChanged;
	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Health", meta=(ClampMin="1", ClampMax="100"))
	float MaxHealth = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Health|Heal")
	bool AutoHeal = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Health|Heal", meta = (EditCondition = "AutoHeal", EditConditionHides))
	float HealRate = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Health|Heal", meta = (EditCondition = "AutoHeal", EditConditionHides))
	float HealDelay = 3.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Health|Heal", meta = (EditCondition = "AutoHeal", EditConditionHides))
	float HealModifier = 1.f;
	
private:
	float Health = 0.0f;

	FTimerHandle HealUpdateTimerHandle;
	
	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	void StartHeal();
	void OnHealUpdate();
};