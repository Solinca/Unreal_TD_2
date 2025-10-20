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
		WeaponsCurrentShotTimer[CurrentIndex] = 0;

		WeaponsCurrentAmmo[CurrentIndex]--;

		FHitResult hit;

		DrawDebugLine(GetWorld(), CameraLocation, CameraLocation + CameraRotation.Vector() * WeaponDatas[CurrentIndex].WeaponRange, FColor::Red, false, 1, 0, 0.5f);

		if (GetWorld()->LineTraceSingleByProfile(hit, CameraLocation, CameraLocation + CameraRotation.Vector() * WeaponDatas[CurrentIndex].WeaponRange, "Bullet"))
		{
			if (UPlayerHealthComponent* HealthComponent = hit.GetActor()->GetComponentByClass<UPlayerHealthComponent>())
			{
				HealthComponent->TakeDamage(WeaponDatas[CurrentIndex].WeaponDamage);
			}
		}

		OnWeaponAmmoChanged.Broadcast(WeaponsCurrentAmmo[CurrentIndex], WeaponDatas[CurrentIndex].MaxAmmunition);

		OnWeaponShot.Broadcast();
	}
}

void UPlayerWeaponComponent::SwitchWeapon(int index)
{
	if (index >= WeaponDatas.Num()) return;

	CurrentIndex = index;

	OnWeaponSwitched.Broadcast(WeaponDatas[CurrentIndex]);

	OnWeaponAmmoChanged.Broadcast(WeaponsCurrentAmmo[CurrentIndex], WeaponDatas[CurrentIndex].MaxAmmunition);
}

void UPlayerWeaponComponent::ReloadWeapon()
{
	WeaponsCurrentAmmo[CurrentIndex] = WeaponDatas[CurrentIndex].MaxAmmunition;

	OnWeaponAmmoChanged.Broadcast(WeaponsCurrentAmmo[CurrentIndex], WeaponDatas[CurrentIndex].MaxAmmunition);
}
