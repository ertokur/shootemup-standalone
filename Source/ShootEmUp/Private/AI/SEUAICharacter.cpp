// Erbol Tokur


#include "AI/SEUAICharacter.h"

#include "BrainComponent.h"
#include "AI/SEUAIController.h"
#include "Components/SEUAIWeaponComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
ASEUAICharacter::ASEUAICharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<USEUAIWeaponComponent>("WeaponComponent"))
{
	AIControllerClass = ASEUAIController::StaticClass();
	
	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}
}

// Called when the game starts or when spawned
void ASEUAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASEUAICharacter::OnDeath()
{
	Super::OnDeath();

	const auto AIController = Cast<AAIController>(Controller);
	if (AIController && AIController->BrainComponent)
	{
		AIController->BrainComponent->Cleanup();
	}
	
}

// Called every frame
void ASEUAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASEUAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

