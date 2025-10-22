#include "GoldCollectible.h"
#include "MyCharacter.h"
#include <Kismet/GameplayStatics.h>
#include <MyGameStateBase.h>

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
		Cast<AMyGameStateBase>(UGameplayStatics::GetGameState(GetWorld()))->GainMoney(GoldGainAmount);

		Mesh->SetVisibility(false, true);
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}
