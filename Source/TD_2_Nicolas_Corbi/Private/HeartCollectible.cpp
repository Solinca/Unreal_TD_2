#include "HeartCollectible.h"
#include <MyCharacter.h>

AHeartCollectible::AHeartCollectible()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Heart");

	Mesh->SetupAttachment(RootComponent);

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AHeartCollectible::OnOverlapBegin);
}

void AHeartCollectible::OnOverlapBegin(UPrimitiveComponent* OverlappingComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UPlayerHealthComponent* PlayerHealthComponent = OtherActor->GetComponentByClass<UPlayerHealthComponent>())
	{
		PlayerHealthComponent->HealHealth(HealthRestoreAmount);

		Mesh->SetVisibility(false, true);
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}
