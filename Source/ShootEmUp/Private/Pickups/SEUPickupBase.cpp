// Erbol Tokur

#include "Pickups/SEUPickupBase.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "UI/SEUPickupCooldownWidget.h"

ASEUPickupBase::ASEUPickupBase()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SetRootComponent(SphereCollision);
	SphereCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SphereCollision->SetSphereRadius(50.f);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(SphereCollision);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

	WidgetComp = CreateDefaultSubobject<UWidgetComponent>("Widget");
	WidgetComp->SetupAttachment(SphereCollision);
	WidgetComp->SetCastShadow(false);
	WidgetComp->SetDrawAtDesiredSize(true);
	WidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetComp->SetVisibility(false);

	RotationComp = CreateDefaultSubobject<URotatingMovementComponent>("RotationComp");
	RotationComp->RotationRate.Yaw = 90.f;
}

void ASEUPickupBase::BeginPlay()
{
	Super::BeginPlay();

	if (PickupCooldownWidgetClass)
	{
		WidgetComp->SetWidgetClass(PickupCooldownWidgetClass);
	}

	GetWorldTimerManager().SetTimer(LoopedCheckHandle, this, &ASEUPickupBase::CheckForOverlappingActors, 0.1f, true, 0.f);
}

void ASEUPickupBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorldTimerManager().ClearTimer(CooldownHandle);
	GetWorldTimerManager().ClearTimer(LoopedCheckHandle);
}

void ASEUPickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASEUPickupBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (TObjectPtr<APawn> Pawn = Cast<APawn>(OtherActor))
	{
		if (OnPickup(Pawn))
		{
			OnStartCooldown();
		}
	}
}

bool ASEUPickupBase::OnPickup(TObjectPtr<APawn> Pawn)
{
	return false;
}

TObjectPtr<class USEUPickupCooldownWidget> ASEUPickupBase::GetCooldownWidget() const
{
	if (WidgetComp)
	{
		if (TObjectPtr<UUserWidget> Widget = WidgetComp->GetWidget())
		{
			return Cast<USEUPickupCooldownWidget>(Widget);
		}
	}

	return nullptr;
}

void ASEUPickupBase::OnStartCooldown()
{
	if (GetWorldTimerManager().IsTimerActive(CooldownHandle))
		return;

	GetWorldTimerManager().ClearTimer(LoopedCheckHandle);
	
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	StaticMesh->SetVisibility(false);
	WidgetComp->SetVisibility(true);
	
	if (TObjectPtr<class USEUPickupCooldownWidget> CooldownWidget = GetCooldownWidget())
	{
		CooldownWidget->OnStartCooldown(CooldownDuration);
	}

	GetWorldTimerManager().SetTimer(CooldownHandle, this, &ASEUPickupBase::OnEndCooldown, CooldownDuration);
}

void ASEUPickupBase::OnEndCooldown()
{
	GetWorldTimerManager().ClearTimer(CooldownHandle);
	
	StaticMesh->SetVisibility(true);
	WidgetComp->SetVisibility(false);

	if (TObjectPtr<class USEUPickupCooldownWidget> CooldownWidget = GetCooldownWidget())
	{
		CooldownWidget->OnEndCooldown();
	}

	SphereCollision->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);

	GetWorldTimerManager().SetTimer(LoopedCheckHandle, this, &ASEUPickupBase::CheckForOverlappingActors, 0.1f, true, 0.f);
}

void ASEUPickupBase::CheckForOverlappingActors()
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors, APawn::StaticClass());

	if (!OverlappingActors.IsEmpty())
	{
		if (AActor* OverlappingActor = OverlappingActors[0])
		{
			NotifyActorBeginOverlap(OverlappingActor);
		}
	}
}