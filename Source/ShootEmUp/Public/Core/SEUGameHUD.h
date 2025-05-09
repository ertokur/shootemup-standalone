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

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
	TSubclassOf<class USEUPlayerWidget> PlayerHUDClass = nullptr;

	virtual void BeginPlay() override;

private:
	void DrawCrosshair();
};