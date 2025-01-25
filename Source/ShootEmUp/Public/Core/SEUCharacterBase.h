// Erbol Tokur

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "SEUCharacterBase.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;
class USEUHealthComponent;
class USEUWeaponComponent;
class ASEUWeaponBase;
class UTextRenderComponent;
struct FInputActionValue;

UCLASS()
class SHOOTEMUP_API ASEUCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ASEUCharacterBase();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Components)
	UCameraComponent* CameraComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Components)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Components)
	USEUHealthComponent* HealthComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Components)
	USEUWeaponComponent* WeaponComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Components)
	UTextRenderComponent* TextRender;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Movement)
	bool IsSprint() const;
protected:
	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputMappingContext* InputContext;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* SprintAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* FireAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* SwitchWeaponAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* ReloadAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Animation)
	UAnimMontage* DeathMontage;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Movement,	meta = (ClampMin = 0, ClampMax = 1000))
	float SprintMoveSpeed = 1000;

private:
	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void Sprint(const FInputActionValue& Value);
	void Fire(const FInputActionValue& Value);

	UFUNCTION()
	void OnDeath();

	UFUNCTION()
	void OnHealthChanged(const float OldHealth, const float NewHealth);
	
private:
	float CachedMaxWalkSpeed = 0;
	bool PressedSprint = false;
	bool MovingForward = false;
};