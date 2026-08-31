// Erbol Tokur


#include "AI/Services/SEUSwitchWeaponService.h"
#include "AIController.h"
#include "Components/SEUWeaponComponent.h"
#include "Dev/SEUUtils.h"

USEUSwitchWeaponService::USEUSwitchWeaponService()
{
	NodeName = "Switch Weapon";
}

void USEUSwitchWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	const AAIController* Controller = OwnerComp.GetAIOwner();
	
	if (Controller)
	{
		if (USEUWeaponComponent* WeaponComp = SEUUtils::GetPlayerComponent<USEUWeaponComponent>(Controller->GetPawn()))
		{
			if (Probability > 0 && FMath::FRand() <= Probability)
			{
				WeaponComp->SwitchWeapon();
			}
		}
	}
	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}