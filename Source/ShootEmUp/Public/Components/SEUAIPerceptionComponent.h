// Erbol Tokur

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "SEUAIPerceptionComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTEMUP_API USEUAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USEUAIPerceptionComponent();
	
	TObjectPtr<AActor> GetClosestEnemy() const;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
