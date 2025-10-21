#include "ZombieSpawner.h"

AZombieSpawner::AZombieSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AZombieSpawner::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle Handle;

	GetWorld()->GetTimerManager().SetTimer(Handle, this, &AZombieSpawner::Spawn, DelayBetweenSpawn, true);
}

void AZombieSpawner::Spawn()
{
	GetWorld()->SpawnActor<AActor>(ZombieToSpawn, FTransform(GetActorLocation()), FActorSpawnParameters());
}
