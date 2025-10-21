#include "GoldCollectible.h"
#include "MyCharacter.h"

AGoldCollectible::AGoldCollectible()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Gold");

	Mesh->SetupAttachment(RootComponent);

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AGoldCollectible::OnOverlapBegin);
}

void AGoldCollectible::OnOverlapBegin(UPrimitiveComponent* OverlappingComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AMyCharacter>(OtherActor))
	{
		// Handle Gold in GameState
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Gold gained : " + FString::FromInt(GoldGainAmount));
	}
}
