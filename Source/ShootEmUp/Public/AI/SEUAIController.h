// Erbol Tokur

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SEUAIController.generated.h"

class USEUAIPerceptionComponent;

UCLASS()
class SHOOTEMUP_API ASEUAIController : public AAIController
{
	GENERATED_BODY()

public:
	ASEUAIController(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName FocusOnKeyName = "EnemyActor";

	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

private:
	AActor* GetFocusOnActor() const;
};