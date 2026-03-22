// Erbol Tokur

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SEUWeaponFXComponent.generated.h"

class UNiagaraSystem;
class UPhysicalMaterial;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTEMUP_API USEUWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USEUWeaponFXComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void PlayImpactFX(const FHitResult& Hit);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = VFX)
	TMap<TObjectPtr<UPhysicalMaterial>, TObjectPtr<UNiagaraSystem>> NiagaraSystemsMap;
};
