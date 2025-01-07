// Erbol Tokur


#include "Components/SEUHealthComponent.h"

USEUHealthComponent::USEUHealthComponent()
{
}

void USEUHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHealth(MaxHealth);
	StartHeal();
	
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &USEUHealthComponent::OnTakeAnyDamage);
}

void USEUHealthComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(HealUpdateTimerHandle);
}

void USEUHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || IsDead())
		return;
	
	SetHealth(GetHealth() - Damage);

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
	
	OnOwnerTakeDamage.Broadcast(DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);

	StartHeal();
}

void USEUHealthComponent::SetHealth(const float NewHealth)
{
	float OldHealth = Health;
	Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(OldHealth, Health);
}

void USEUHealthComponent::StartHeal()
{
	if (!AutoHeal || !GetWorld() || IsDead())
		return;
	
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	if (TimerManager.IsTimerActive(HealUpdateTimerHandle))
	{
		TimerManager.ClearTimer(HealUpdateTimerHandle);
	}

	TimerManager.SetTimer(HealUpdateTimerHandle, this, &USEUHealthComponent::OnHealUpdate, HealRate, true, HealDelay);
}

void USEUHealthComponent::OnHealUpdate()
{
	if (!AutoHeal || !GetWorld() || IsDead())
		return;
	
	SetHealth(GetHealth()+HealModifier);
	UE_LOG(LogTemp, Warning, TEXT("HEAL = %f"), Health);

	if (FMath::IsNearlyEqual(GetHealth(), MaxHealth))
	{
		GetWorld()->GetTimerManager().ClearTimer(HealUpdateTimerHandle);
	}
}