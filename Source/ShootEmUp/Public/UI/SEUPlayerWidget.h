// Erbol Tokur

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Core/SEUCoreTypes.h"
#include "SEUPlayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTEMUP_API USEUPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = UI)
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = UI)
	bool GetWeaponUIData(FWeaponUIData& UIData) const;

	UFUNCTION(BlueprintCallable, Category = UI)
	bool GetWeaponAmmoData(FAmmoData& AmmoData) const;

	UFUNCTION(BlueprintCallable, Category = UI)
	bool IsPlayerAlive() const;

	UFUNCTION(BlueprintCallable, Category = UI)
	bool IsPlayerSpectating() const;
};