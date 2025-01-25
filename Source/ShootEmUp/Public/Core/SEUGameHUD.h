// Erbol Tokur

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SEUGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTEMUP_API ASEUGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

private:
	void DrawCrosshair();
};