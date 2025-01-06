// Erbol Tokur

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SEUCharacterBase.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class SHOOTEMUP_API ASEUCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASEUCharacterBase();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Components)
	UCameraComponent* CameraComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Components)
	USpringArmComponent* SpringArm;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Movement,	meta = (ClampMin = 0, ClampMax = 1000))
	float SprintMoveSpeed = 1000;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Movement)
	bool IsSprint() const;

private:
	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void Sprint(const FInputActionValue& Value);
	
private:
	float CachedMaxWalkSpeed = 0;
	bool PressedSprint = false;
	bool MovingForward = false;
};
