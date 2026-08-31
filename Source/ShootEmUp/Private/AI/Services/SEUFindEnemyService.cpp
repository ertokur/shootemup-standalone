// Erbol Tokur


#include "AI/Services/SEUFindEnemyService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SEUAIPerceptionComponent.h"

USEUFindEnemyService::USEUFindEnemyService()
{
	NodeName = "Find Enemy Service";
}

void USEUFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent())
	{
		AAIController* Controller = OwnerComp.GetAIOwner();
		if (USEUAIPerceptionComponent* Perception = Controller->FindComponentByClass<USEUAIPerceptionComponent>())
		{
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, Perception->GetClosestEnemy());
		}
	}
	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
