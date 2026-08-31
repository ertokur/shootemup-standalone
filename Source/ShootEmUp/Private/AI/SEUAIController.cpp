// Erbol Tokur

#include "AI/SEUAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SEUAIPerceptionComponent.h"

ASEUAIController::ASEUAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<USEUAIPerceptionComponent>("PerceptionComponent");
	SetPerceptionComponent(*AIPerceptionComponent);
}

void ASEUAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ASEUAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetFocus(GetFocusOnActor());
}

AActor* ASEUAIController::GetFocusOnActor() const
{
	if (!GetBlackboardComponent()) return nullptr;
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}