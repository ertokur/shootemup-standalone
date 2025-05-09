// Erbol Tokur

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SEUPickupBase.generated.h"


UCLASS()
class SHOOTEMUP_API ASEUPickupBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ASEUPickupBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<class USphereComponent> SphereCollision = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<class UStaticMeshComponent> StaticMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<class UWidgetComponent> WidgetComp = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<class URotatingMovementComponent> RotationComp = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Settings)
	float CooldownDuration = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Settings)
	TSubclassOf<class USEUPickupCooldownWidget> PickupCooldownWidgetClass = nullptr;

	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	virtual bool OnPickup(TObjectPtr<APawn> Pawn);
	TObjectPtr<class USEUPickupCooldownWidget> GetCooldownWidget() const;

private:
	void OnStartCooldown();
	void OnEndCooldown();
	void CheckForOverlappingActors();
	
	FTimerHandle CooldownHandle;
	FTimerHandle LoopedCheckHandle;
};