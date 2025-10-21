#include "PlayerWeaponComponent.h"
#include <PlayerHealthComponent.h>

UPlayerWeaponComponent::UPlayerWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	for (FWeaponData data : WeaponDatas)
	{
		WeaponsCurrentAmmo.Add(data.MaxAmmunition);
		WeaponsCurrentShotTimer.Add(data.TimeBetweenShotInSeconds);
	}

	SwitchWeapon(CurrentIndex);
}

void UPlayerWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	WeaponsCurrentShotTimer[CurrentIndex] += DeltaTime;
}

void UPlayerWeaponComponent::HandleShoot(FVector CameraLocation, FRotator CameraRotation)
{
	if (WeaponsCurrentShotTimer[CurrentIndex] >= WeaponDatas[CurrentIndex].TimeBetweenShotInSeconds && WeaponsCurrentAmmo[CurrentIndex] > 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(Handle);

		WeaponsCurrentShotTimer[CurrentIndex] = 0;

		if (!isUnlimitedAmmo)
		{
			WeaponsCurrentAmmo[CurrentIndex]--;
		}

		FHitResult hit;

		DrawDebugLine(GetWorld(), CameraLocation, CameraLocation + CameraRotation.Vector() * WeaponDatas[CurrentIndex].WeaponRange, FColor::Red, false, 1, 0, 0.5f);

		if (GetWorld()->LineTraceSingleByProfile(hit, CameraLocation, CameraLocation + CameraRotation.Vector() * WeaponDatas[CurrentIndex].WeaponRange, "Bullet"))
		{
			if (UPlayerHealthComponent* HealthComponent = hit.GetActor()->GetComponentByClass<UPlayerHealthComponent>())
			{
				HealthComponent->TakeDamage(WeaponDatas[CurrentIndex].WeaponDamage);

				if (HealthComponent->GetCurrentHealth() == 0)
				{
					// Handle Score in GameState
					OnKillScored.Broadcast(WeaponDatas[CurrentIndex].WeaponScore);
				}
			}
		}

		OnWeaponAmmoChanged.Broadcast(WeaponsCurrentAmmo[CurrentIndex], WeaponDatas[CurrentIndex].MaxAmmunition);
	}
}

void UPlayerWeaponComponent::SwitchWeapon(int index)
{
	if (index >= WeaponDatas.Num()) return;

	GetWorld()->GetTimerManager().ClearTimer(Handle);

	CurrentIndex = index;

	WeaponMeshComponent->SetStaticMesh(WeaponDatas[CurrentIndex].WeaponMesh);

	WeaponMeshComponent->AttachToComponent(WeaponMeshComponent->GetAttachParent(), FAttachmentTransformRules::KeepRelativeTransform , WeaponDatas[CurrentIndex].WeaponSocket);

	OnWeaponAmmoChanged.Broadcast(WeaponsCurrentAmmo[CurrentIndex], WeaponDatas[CurrentIndex].MaxAmmunition);
}

void UPlayerWeaponComponent::ReloadWeapon()
{
	if (WeaponsCurrentAmmo[CurrentIndex] != WeaponDatas[CurrentIndex].MaxAmmunition)
	{
		GetWorld()->GetTimerManager().SetTimer(Handle, this, &UPlayerWeaponComponent::ReloadOneAmmo, WeaponDatas[CurrentIndex].ReloadInterval, true);
	}
}

void UPlayerWeaponComponent::ReloadOneAmmo()
{
	WeaponsCurrentAmmo[CurrentIndex]++;

	if (WeaponsCurrentAmmo[CurrentIndex] == WeaponDatas[CurrentIndex].MaxAmmunition)
	{
		GetWorld()->GetTimerManager().ClearTimer(Handle);
	}

	OnWeaponAmmoChanged.Broadcast(WeaponsCurrentAmmo[CurrentIndex], WeaponDatas[CurrentIndex].MaxAmmunition);
}

void UPlayerWeaponComponent::SetMesh(UStaticMeshComponent* mesh)
{
	WeaponMeshComponent = mesh;
}

void UPlayerWeaponComponent::TriggerUnlimitedAmmoBonus(float duration)
{
	isUnlimitedAmmo = true;

	FTimerHandle UnlimitedAmmoHandle;

	GetWorld()->GetTimerManager().SetTimer(UnlimitedAmmoHandle, this, &UPlayerWeaponComponent::CancelUnlimitedAmmoBonus, duration, false);

	OnUnlimitedAmmoBonus.Broadcast(true);
}

void UPlayerWeaponComponent::CancelUnlimitedAmmoBonus()
{
	isUnlimitedAmmo = false;

	OnUnlimitedAmmoBonus.Broadcast(false);
}
