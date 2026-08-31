// Erbol Tokur

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SEUFireService.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTEMUP_API USEUFireService : public UBTService
{
	GENERATED_BODY()
	
public:
	USEUFireService();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI");
	FBlackboardKeySelector EnemyActorKey;
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
