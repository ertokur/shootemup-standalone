// Erbol Tokur

#pragma once

#include "CoreMinimal.h"
#include "Pickups/SEUPickupBase.h"
#include "SEUAmmoPickup.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTEMUP_API ASEUAmmoPickup : public ASEUPickupBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Settings)
	int32 AmmoAmount = 0;
	
protected:
	virtual bool OnPickup(TObjectPtr<APawn> Pawn) override;
};