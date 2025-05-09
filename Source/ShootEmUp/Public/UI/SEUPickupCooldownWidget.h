// Erbol Tokur

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetMathLibrary.h"
#include "SEUPickupCooldownWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTEMUP_API USEUPickupCooldownWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void OnStartCooldown(const float CooldownDuration);
	void OnEndCooldown();

	UFUNCTION(BlueprintCallable, Category = UI)
	FORCEINLINE float GetCooldownPercent() const { return UKismetMathLibrary::SafeDivide(CurrentTimestamp, TotalDuration); }

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	float TotalDuration = 0.f;
	float CurrentTimestamp = 0.f;
	bool bCooldownStarted = false;
};
