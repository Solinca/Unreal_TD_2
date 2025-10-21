#include "BonusCollectible.h"
#include "MyCharacter.h"

ABonusCollectible::ABonusCollectible()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Bonus");

	Mesh->SetupAttachment(RootComponent);

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ABonusCollectible::OnOverlapBegin);
}

void ABonusCollectible::OnOverlapBegin(UPrimitiveComponent* OverlappingComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UPlayerWeaponComponent* PlayerWeaponComponent = OtherActor->GetComponentByClass<UPlayerWeaponComponent>())
	{
		PlayerWeaponComponent->TriggerUnlimitedAmmoBonus(Duration);

		Mesh->SetVisibility(false, true);
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}
