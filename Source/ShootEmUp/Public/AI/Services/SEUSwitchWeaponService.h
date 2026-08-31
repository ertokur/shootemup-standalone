// Erbol Tokur

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SEUSwitchWeaponService.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTEMUP_API USEUSwitchWeaponService : public UBTService
{
	GENERATED_BODY()
	
public:
	USEUSwitchWeaponService();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = 0, ClampMax = 1))
	float Probability = 0.5f;
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
