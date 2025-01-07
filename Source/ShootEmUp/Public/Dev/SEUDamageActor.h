// Erbol Tokur

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SEUDamageActor.generated.h"

UCLASS()
class SHOOTEMUP_API ASEUDamageActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASEUDamageActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* SceneComponent;
	
	UPROPERTY(EditAnywhere, Category = Damage)
	float Radius = 300.0f;

	UPROPERTY(EditAnywhere, Category = Damage)
	FColor SphereColor = FColor::Black;

	UPROPERTY(EditAnywhere, Category = Damage)
	float DamagePerSec = 5.f;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};