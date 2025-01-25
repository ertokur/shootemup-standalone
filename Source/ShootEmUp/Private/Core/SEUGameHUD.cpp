// Erbol Tokur


#include "Core/SEUGameHUD.h"
#include "Engine/Canvas.h"

void ASEUGameHUD::DrawHUD()
{
	Super::DrawHUD();
	DrawCrosshair();
}

void ASEUGameHUD::DrawCrosshair()
{
	const TInterval<float> Center(Canvas->SizeX / 2, Canvas->SizeY / 2);
	const float HalfLineSize = 10.0f;
	const float LineThickness = 2.0f;
	const FLinearColor LineColor = FLinearColor::Blue;
	
	DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness);
	DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness);
}