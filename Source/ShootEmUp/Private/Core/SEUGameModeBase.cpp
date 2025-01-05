// Erbol Tokur


#include "Core/SEUGameModeBase.h"
#include "Core/SEUCharacterBase.h"
#include "Core/SEUPlayerController.h"

ASEUGameModeBase::ASEUGameModeBase()
{
	DefaultPawnClass = ASEUCharacterBase::StaticClass();
	PlayerControllerClass = ASEUPlayerController::StaticClass();
}
