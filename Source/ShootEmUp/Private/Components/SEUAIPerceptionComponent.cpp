// Erbol Tokur


#include "Components/SEUAIPerceptionComponent.h"
#include "AIController.h"
#include "Components/SEUHealthComponent.h"
#include "Dev/SEUUtils.h"
#include "Kismet/KismetMathLibrary.h"
#include "Perception/AISense_Sight.h"


// Sets default values for this component's properties
USEUAIPerceptionComponent::USEUAIPerceptionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

TObjectPtr<AActor> USEUAIPerceptionComponent::GetClosestEnemy() const
{
	TArray<AActor*> Actors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), Actors);
	
	if (Actors.IsEmpty())
		return nullptr;
	
	TObjectPtr<AAIController> Controller = Cast<AAIController>(GetOwner());
	if (!Controller) return nullptr;
	
	TObjectPtr<APawn> Pawn = Controller->GetPawn();
	if (!Pawn) return nullptr;
	
	float MinDistance = MAX_FLT;
	TObjectPtr<AActor> OutActor = nullptr;
	
	for (AActor* Actor : Actors)
	{
		if (TObjectPtr<USEUHealthComponent> HealthComp = Actor->FindComponentByClass<USEUHealthComponent>())
		{
			if (!HealthComp->IsDead())
			{
				double CurrentDistance = UKismetMathLibrary::Vector_Distance(Actor->GetActorLocation(), Pawn->GetActorLocation());
				if (CurrentDistance < MinDistance)
				{
					MinDistance = CurrentDistance;
					OutActor = Actor;
				}
			}
		}
	}
	
	return OutActor;
}


// Called when the game starts
void USEUAIPerceptionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USEUAIPerceptionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

