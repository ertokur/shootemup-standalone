// Erbol Tokur

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SEUNextLocationTask.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTEMUP_API USEUNextLocationTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	USEUNextLocationTask();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius = 1000.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector LocationKey;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool SelfCenter = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "!SelfCenter"))
	FBlackboardKeySelector CenterActorKey;
};
