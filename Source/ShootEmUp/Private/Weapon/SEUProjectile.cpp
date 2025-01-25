// Erbol Tokur


#include "Weapon/SEUProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ASEUProjectile::ASEUProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	CollisionComp->SetCollisionResponseToChannels(ECollisionResponse::ECR_Block);
	CollisionComp->IgnoreActorWhenMoving(GetOwner(), true);
	RootComponent = CollisionComp;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
}

void ASEUProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(10.0f);
	OnActorHit.AddDynamic(this, &ASEUProjectile::OnHit);
}

void ASEUProjectile::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!GetWorld() || !ExplosionParticles)
		return;
	
	UE_LOG(LogTemp, Display, TEXT("OnHit"));
	OnProjectileHit.Broadcast(SelfActor, OtherActor, NormalImpulse, Hit);

	ProjectileMovement->StopMovementImmediately();
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticles, Hit.Location);

	UGameplayStatics::ApplyRadialDamage(GetWorld(), BaseDamage, Hit.Location, DamageRadius, UDamageType::StaticClass(), { GetOwner() }, this, GetController());
	DrawDebugSphere(GetWorld(), Hit.Location, DamageRadius,24, FColor::Red, false, 3.0f);
	
	Destroy();
}

AController* ASEUProjectile::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}