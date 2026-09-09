// Erbol Tokur

#pragma once

#include "CoreMinimal.h"
#include "Core/SEUCharacterBase.h"
#include "SEUAICharacter.generated.h"

UCLASS()
class SHOOTEMUP_API ASEUAICharacter : public ASEUCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASEUAICharacter(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void OnDeath() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
