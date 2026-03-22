// Erbol Tokur


#include "Weapon/Components/SEUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

USEUWeaponFXComponent::USEUWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void USEUWeaponFXComponent::BeginPlay()
{
	Super::BeginPlay();
}


void USEUWeaponFXComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void USEUWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	if (Hit.PhysMaterial.IsValid())
	{
		if (NiagaraSystemsMap.Contains(Hit.PhysMaterial.Get()))
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, NiagaraSystemsMap[Hit.PhysMaterial.Get()], Hit.Location, Hit.ImpactNormal.Rotation(), FVector(1), true);
		}
	}
}