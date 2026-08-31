// Erbol Tokur


#include "AI/Services/SEUFireService.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SEUWeaponComponent.h"
#include "Dev/SEUUtils.h"

USEUFireService::USEUFireService()
{
	NodeName = "Fire Service";
}

void USEUFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	const AAIController* Controller = OwnerComp.GetAIOwner();
	
	const bool bHasTarget = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);
	
	if (Controller)
	{
		if (USEUWeaponComponent* WeaponComp = SEUUtils::GetPlayerComponent<USEUWeaponComponent>(Controller->GetPawn()))
		{
			bHasTarget ? WeaponComp->StartFire() : WeaponComp->StopFire();
		}
	}
	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
