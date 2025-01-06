// Erbol Tokur


#include "Core/SEUCharacterBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"

// Sets default values
ASEUCharacterBase::ASEUCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArm  = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArm->SetupAttachment(RootComponent);
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComp->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ASEUCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	CachedMaxWalkSpeed = Cast<UCharacterMovementComponent>(GetMovementComponent())->GetMaxSpeed();
}

// Called every frame
void ASEUCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASEUCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (!InputContext) return;
	
	ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Cast<APlayerController>(GetController())->Player);

	if (!LocalPlayer) return;

	UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	if (!InputSystem) return;

	InputSystem->ClearAllMappings();
	InputSystem->AddMappingContext(InputContext, 0);

	UEnhancedInputComponent* InputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (!InputComp) return;

	InputComp->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASEUCharacterBase::Look);
	InputComp->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASEUCharacterBase::Move);
	InputComp->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
	InputComp->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	InputComp->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ASEUCharacterBase::Sprint);
}

bool ASEUCharacterBase::IsSprint() const
{
	return PressedSprint && MovingForward && GetVelocity().Length() > 0;
}

void ASEUCharacterBase::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ASEUCharacterBase::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		MovingForward = MovementVector.Y > 0 && FMath::IsNearlyZero(MovementVector.X, 0.2);

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);

		if (UCharacterMovementComponent* CharMoveComp = Cast<UCharacterMovementComponent>(GetMovementComponent()))
		{
			CharMoveComp->MaxWalkSpeed = IsSprint() ? SprintMoveSpeed : CachedMaxWalkSpeed;
		}
	}
}
void ASEUCharacterBase::Sprint(const FInputActionValue& Value)
{
	PressedSprint = Value.Get<bool>();
}