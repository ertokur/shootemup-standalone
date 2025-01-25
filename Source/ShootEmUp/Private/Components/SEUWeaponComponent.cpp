// Erbol Tokur


#include "Components/SEUWeaponComponent.h"
#include "Weapon/SEUWeaponBase.h"
#include "GameFramework/Character.h"
#include "Animation/SEUEquipFinishedAnimNotify.h"
#include "Animation/SEUReloadFinishedAnimNotify.h"
#include "Animation/SEUAnimUtils.h"
#include "Core/SEUCoreTypes.h"

static int8 WeaponCount = 2;

USEUWeaponComponent::USEUWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USEUWeaponComponent::StartFire()
{
	if (CanFire())
	{
		CurrentWeapon->StartFire();
	}
}

void USEUWeaponComponent::StopFire()
{
	if (!CurrentWeapon)
		return;

	CurrentWeapon->StopFire();
}

void USEUWeaponComponent::SwitchWeapon()
{
	if (CanEquip())
	{
		CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
		EquipWeapon(CurrentWeaponIndex);
	}
}

void USEUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	ensureMsgf(StartingWeaponData.Num() == WeaponCount, TEXT("Our character can hold only %i weapon items!"), WeaponCount);
	
	InitAnimNotifies();
	SpawnWeapons();
	EquipWeapon(CurrentWeaponIndex);
}

void USEUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon = nullptr;
	for (auto Iter : Weapons)
	{
		Iter->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Iter->Destroy();
	}
	Weapons.Empty();

	Super::EndPlay(EndPlayReason);
}

void USEUWeaponComponent::SpawnWeapons()
{
	if (!GetWorld())
		return;
	
	if (ACharacter* Owner = Cast<ACharacter>(GetOwner()))
	{
		for (const auto& Iter : StartingWeaponData)
		{
			if (Iter.WeaponClass)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = GetOwner();
				const auto& NewWeapon = GetWorld()->SpawnActor<ASEUWeaponBase>(Iter.WeaponClass, SpawnParams);

				if (NewWeapon)
				{
					Weapons.Add(NewWeapon);

					AttachWeaponToSocket(NewWeapon, "SOCKET_Armory");
				}
			}
		}
	}
}

void USEUWeaponComponent::Reload()
{
	OnChangeClip();
}

void USEUWeaponComponent::AttachWeaponToSocket(ASEUWeaponBase* Weapon, const FName& SocketName)
{
	if (!Weapon || !Cast<ACharacter>(GetOwner()))
		return;
	
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(Cast<ACharacter>(GetOwner())->GetMesh(), AttachmentRules, SocketName);
}

void USEUWeaponComponent::EquipWeapon(int16 WeaponIndex)
{
	if (ACharacter* Owner = Cast<ACharacter>(GetOwner()))
	{
		if (CurrentWeapon)
		{
			AttachWeaponToSocket(CurrentWeapon, "SOCKET_Armory");
			CurrentWeapon->StopFire();
			if (CurrentWeapon->OnClipEmpty.IsBound())
			{
				CurrentWeapon->OnClipEmpty.Remove(ClipEmptyDelegateHandle);
			}
		}
		
		if (Weapons.IsValidIndex(WeaponIndex))
		{
			CurrentWeapon = Weapons[WeaponIndex];
			CurrentWeaponIndex = WeaponIndex;
			ClipEmptyDelegateHandle = CurrentWeapon->OnClipEmpty.AddUObject(this, &USEUWeaponComponent::OnEmptyClip);
			
			bIsEquipping = true;
			AttachWeaponToSocket(CurrentWeapon, "SOCKET_Weapon");
			PlayAnimMontage(EquipMontage);
		}
	}
}

void USEUWeaponComponent::PlayAnimMontage(UAnimMontage* AnimMontage)
{
	if (ACharacter* Owner = Cast<ACharacter>(GetOwner()))
	{
		Owner->PlayAnimMontage(AnimMontage);
	}
}

void USEUWeaponComponent::InitAnimNotifies()
{
	if (auto EquipFinishedNotify = SEUAnimUtils::FindNotifyByClass<USEUEquipFinishedAnimNotify>(EquipMontage))
	{
		EquipFinishedNotify->OnNotifyFinished.AddUObject(this, &USEUWeaponComponent::OnEquipFinished);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Equip anim notify is forgotten to set"));
		checkNoEntry();
	}
	
	for (auto Iter : StartingWeaponData)
	{
		if (auto ReloadFinishedNotify = SEUAnimUtils::FindNotifyByClass<USEUReloadFinishedAnimNotify>(Iter.ReloadAnimMontage))
		{
			ReloadFinishedNotify->OnNotifyFinished.AddUObject(this, &USEUWeaponComponent::OnReloadFinished);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Reload anim notify is forgotten to set"));
			checkNoEntry();
		}
	}
	
}

void USEUWeaponComponent::OnEquipFinished(TObjectPtr<USkeletalMeshComponent> SkeletalMeshComp)
{
	if (ACharacter* Owner = Cast<ACharacter>(GetOwner()))
	{
		if (Owner->GetMesh() == SkeletalMeshComp)
		{
			bIsEquipping = false;	
		}
	}
}

void USEUWeaponComponent::OnReloadFinished(TObjectPtr<USkeletalMeshComponent> SkeletalMeshComp)
{
	if (ACharacter* Owner = Cast<ACharacter>(GetOwner()))
	{
		if (Owner->GetMesh() == SkeletalMeshComp)
		{
			bIsReloading = false;	
		}
	}
}

bool USEUWeaponComponent::CanFire() const
{
	return IsValid(CurrentWeapon) && !bIsEquipping && !bIsReloading;
}

bool USEUWeaponComponent::CanEquip() const
{
	return !bIsEquipping && !bIsReloading;
}

bool USEUWeaponComponent::CanReload() const
{
	return IsValid(CurrentWeapon) && !bIsEquipping && !bIsReloading && CurrentWeapon->CanReload();
}

void USEUWeaponComponent::OnEmptyClip()
{
	OnChangeClip();
}

void USEUWeaponComponent::OnChangeClip()
{
	if (!GetOwner() || !CanReload())
		return;
	
	TObjectPtr<UAnimMontage> ReloadAnimMontage = nullptr;
	
	for (const auto Iter : StartingWeaponData)
	{
		if (Iter.WeaponClass == CurrentWeapon->GetClass())
		{
			ReloadAnimMontage = Iter.ReloadAnimMontage;
			break;
		}
	}

	if (ReloadAnimMontage)
	{
		StopFire();
		bIsReloading = true;
		PlayAnimMontage(ReloadAnimMontage);
		CurrentWeapon->Reload();
	}
}