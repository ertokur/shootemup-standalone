// Erbol Tokur


#include "AI/Tasks/SEUNextLocationTask.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"


USEUNextLocationTask::USEUNextLocationTask()
{
	NodeName = "Select Next Location";
}

EBTNodeResult::Type USEUNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const TObjectPtr<AAIController> Controller = OwnerComp.GetAIOwner();
	const TObjectPtr<UBlackboardComponent> Blackboard = OwnerComp.GetBlackboardComponent();
	
	if (!Controller || !Blackboard)
		return EBTNodeResult::Failed;
	
	const TObjectPtr<APawn> Pawn = Controller->GetPawn();
	
	if (!Pawn)
		return EBTNodeResult::Failed;
	
	const TObjectPtr<UNavigationSystemV1> NavSystem = UNavigationSystemV1::GetCurrent(Pawn);
	
	if (!NavSystem)
		return EBTNodeResult::Failed;
	
	FNavLocation ResultLocation;
	FVector Location = Pawn->GetActorLocation();
	
	if (!SelfCenter)
	{
		AActor* CenterActor = Cast<AActor>(Blackboard->GetValueAsObject(CenterActorKey.SelectedKeyName));
		
		if (!CenterActor)
			return EBTNodeResult::Failed;
		
		Location = CenterActor->GetActorLocation();
	}
	
	const bool bFound = NavSystem->GetRandomReachablePointInRadius(Location, Radius, ResultLocation);
	
	if (!bFound)
		return EBTNodeResult::Failed;
	
	Blackboard->SetValueAsVector(LocationKey.SelectedKeyName, ResultLocation.Location);
	
	return EBTNodeResult::Succeeded;
}
