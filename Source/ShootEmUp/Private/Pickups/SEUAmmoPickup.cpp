// Erbol Tokur


#include "Pickups/SEUAmmoPickup.h"

#include "Components/SEUHealthComponent.h"
#include "Components/SEUWeaponComponent.h"
#include "Dev/SEUUtils.h"

bool ASEUAmmoPickup::OnPickup(TObjectPtr<APawn> Pawn)
{
	if (const auto HealthComp = SEUUtils::GetPlayerComponent<USEUHealthComponent>(Pawn))
	{
		if (!HealthComp->IsDead())
		{
			if (const auto WeaponComp = SEUUtils::GetPlayerComponent<USEUWeaponComponent>(Pawn))
			{
				return WeaponComp->TryToAddAmmo(AmmoAmount);
			}
		}
	}
	
	return false;
}