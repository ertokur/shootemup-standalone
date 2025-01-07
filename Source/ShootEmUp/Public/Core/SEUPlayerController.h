// Erbol Tokur

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SEUPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTEMUP_API ASEUPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
};