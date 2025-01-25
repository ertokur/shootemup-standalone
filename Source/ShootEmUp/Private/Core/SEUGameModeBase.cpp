// Erbol Tokur


#include "Core/SEUGameModeBase.h"
#include "Core/SEUCharacterBase.h"
#include "Core/SEUPlayerController.h"
#include "Core/SEUGameHUD.h"

ASEUGameModeBase::ASEUGameModeBase()
{
	DefaultPawnClass = ASEUCharacterBase::StaticClass();
	PlayerControllerClass = ASEUPlayerController::StaticClass();
	HUDClass = ASEUGameHUD::StaticClass();
}