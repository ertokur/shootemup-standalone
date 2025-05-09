// Erbol Tokur

#pragma once

#include "CoreMinimal.h"
#include "Pickups/SEUPickupBase.h"
#include "SEUHealPickup.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTEMUP_API ASEUHealPickup : public ASEUPickupBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Settings)
	float HealthAmount = 0.f;
	
protected:
	virtual bool OnPickup(TObjectPtr<APawn> Pawn) override;
};