// Erbol Tokur


#include "UI/SEUPickupCooldownWidget.h"

void USEUPickupCooldownWidget::OnStartCooldown(const float CooldownDuration)
{
	bCooldownStarted = true;
	TotalDuration = CooldownDuration;
}

void USEUPickupCooldownWidget::OnEndCooldown()
{
	bCooldownStarted = false;
	CurrentTimestamp = 0.f;
}

void USEUPickupCooldownWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bCooldownStarted)
	{
		CurrentTimestamp += InDeltaTime;
	}
}