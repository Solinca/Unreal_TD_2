#include "MyCharacter.h"

AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");

	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetupAttachment(SpringArm);

	PlayerHealthComponent = CreateDefaultSubobject<UPlayerHealthComponent>("Player Health");

	PlayerWeaponComponent = CreateDefaultSubobject<UPlayerWeaponComponent>("Player Weapon");

	PlayerWeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("Player Weapon Mesh");

	PlayerWeaponMesh->SetupAttachment(GetMesh());
}

void AMyCharacter::ForwardShoot()
{
	if (PlayerWeaponComponent)
	{
		PlayerWeaponComponent->HandleShoot();
	}
}

void AMyCharacter::ForwardSwitchWeapon(int index)
{
	if (PlayerWeaponComponent)
	{
		PlayerWeaponComponent->SwitchWeapon(index);
	}
}

void AMyCharacter::ForwardReloadWeapon()
{
	if (PlayerWeaponComponent)
	{
		PlayerWeaponComponent->ReloadWeapon();
	}
}
