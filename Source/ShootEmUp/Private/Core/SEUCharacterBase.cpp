// Erbol Tokur


#include "Core/SEUCharacterBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/SEUHealthComponent.h"
#include "Components/SEUWeaponComponent.h"
#include "Weapon/SEUWeaponBase.h"

ASEUCharacterBase::ASEUCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArm  = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArm->SetupAttachment(RootComponent);
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComp->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);
	
	HealthComp = CreateDefaultSubobject<USEUHealthComponent>("HealthComponent");
	WeaponComp = CreateDefaultSubobject<USEUWeaponComponent>("WeaponComponent");
}

void ASEUCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	CachedMaxWalkSpeed = Cast<UCharacterMovementComponent>(GetMovementComponent())->GetMaxSpeed();

	check(HealthComp);

	if (!HealthComp->OnDeath.IsBound())
	{
		HealthComp->OnDeath.AddDynamic(this, &ASEUCharacterBase::OnDeath);
	}
	
	HealthComp->OnHealthChanged.AddDynamic(this, &ASEUCharacterBase::OnHealthChanged);
	OnHealthChanged(0, HealthComp->GetHealth());
}

void ASEUCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASEUCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	check(WeaponComp);
	
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
	InputComp->BindAction(FireAction, ETriggerEvent::Triggered, this, &ASEUCharacterBase::Fire);
	InputComp->BindAction(SwitchWeaponAction, ETriggerEvent::Triggered, WeaponComp, &USEUWeaponComponent::SwitchWeapon);
	InputComp->BindAction(ReloadAction, ETriggerEvent::Triggered, WeaponComp, &USEUWeaponComponent::Reload);
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

void ASEUCharacterBase::Fire(const FInputActionValue& Value)
{
	if (!WeaponComp)
		return;

	Value.Get<bool>() ? WeaponComp->StartFire() : WeaponComp->StopFire();
}

void ASEUCharacterBase::OnDeath()
{
	PlayAnimMontage(DeathMontage);
	WeaponComp->StopFire();
	GetCharacterMovement()->DisableMovement();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	SetLifeSpan(5.0f);

	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}

void ASEUCharacterBase::OnHealthChanged(const float OldHealth, const float NewHealth)
{
}