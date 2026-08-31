// Erbol Tokur

#pragma once

#include "CoreMinimal.h"
#include "SEUWeaponComponent.h"
#include "SEUAIWeaponComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTEMUP_API USEUAIWeaponComponent : public USEUWeaponComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USEUAIWeaponComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void StartFire() override;
	virtual void SwitchWeapon() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
