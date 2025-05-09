// Erbol Tokur


#include "Pickups/SEUHealPickup.h"
#include "Components/SEUHealthComponent.h"
#include "Dev/SEUUtils.h"

bool ASEUHealPickup::OnPickup(TObjectPtr<APawn> Pawn)
{
	if (const auto HealthComp = SEUUtils::GetPlayerComponent<USEUHealthComponent>(Pawn))
	{
		return HealthComp->TryToAddHealth(HealthAmount);
	}
	
	return false;
}