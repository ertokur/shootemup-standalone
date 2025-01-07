// Erbol Tokur


#include "Dev/SEUDamageActor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASEUDamageActor::ASEUDamageActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetCanBeDamaged(false);
	
	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	RootComponent = SceneComponent;
}

// Called when the game starts or when spawned
void ASEUDamageActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASEUDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 32, SphereColor);

	float ResultDamage = DamagePerSec*DeltaTime;
	UGameplayStatics::ApplyRadialDamage(GetWorld(), ResultDamage, GetActorLocation(), Radius, UDamageType::StaticClass(), {}, this,nullptr,true);
}