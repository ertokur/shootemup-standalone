// Erbol Tokur


#include "UI/SEUPlayerWidget.h"
#include "Components/SEUHealthComponent.h"
#include "Components/SEUWeaponComponent.h"
#include "Dev/SEUUtils.h"

float USEUPlayerWidget::GetHealthPercent() const
{
	if (const auto HealthComp = SEUUtils::GetPlayerComponent<USEUHealthComponent>(GetOwningPlayerPawn()))
	{
		return HealthComp->GetHealthPercent();
	}

	return 0.f;
}

bool USEUPlayerWidget::GetWeaponUIData(FWeaponUIData& UIData) const
{
	if (const auto WeaponComp = SEUUtils::GetPlayerComponent<USEUWeaponComponent>(GetOwningPlayerPawn()))
	{
		return WeaponComp->GetWeaponUIData(UIData);
	}

	return false;
}

bool USEUPlayerWidget::GetWeaponAmmoData(FAmmoData& AmmoData) const
{
	if (const auto WeaponComp = SEUUtils::GetPlayerComponent<USEUWeaponComponent>(GetOwningPlayerPawn()))
	{
		return WeaponComp->GetWeaponAmmoData(AmmoData);
	}

	return false;
}

bool USEUPlayerWidget::IsPlayerAlive() const
{
	if (const auto HealthComp = SEUUtils::GetPlayerComponent<USEUHealthComponent>(GetOwningPlayerPawn()))
	{
		return !HealthComp->IsDead();
	}

	return false;
}

bool USEUPlayerWidget::IsPlayerSpectating() const
{
	if (const auto Owner = GetOwningPlayer())
	{
		return Owner->GetStateName() == NAME_Spectating;
	}
	
	return false;
}