// Erbol Tokur


#include "Components/SEUAIWeaponComponent.h"

#include "Weapon/SEUWeaponBase.h"


// Sets default values for this component's properties
USEUAIWeaponComponent::USEUAIWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USEUAIWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void USEUAIWeaponComponent::StartFire()
{
	if (CanFire())
	{
		if (CurrentWeapon->IsAmmoEmpty())
		{
			SwitchWeapon();
		}
		else
		{
			CurrentWeapon->StartFire();
		}
	}
}

void USEUAIWeaponComponent::SwitchWeapon()
{
	if (CanEquip())
	{
		int32 NextIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
		
		while (NextIndex != CurrentWeaponIndex)
		{
			if (!Weapons[NextIndex]->IsAmmoEmpty()) break;
			NextIndex = (NextIndex + 1) % Weapons.Num();
		}
		
		if (NextIndex != CurrentWeaponIndex)
		{
			CurrentWeaponIndex = NextIndex;
			EquipWeapon(CurrentWeaponIndex);
		}
	}
}


// Called every frame
void USEUAIWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

