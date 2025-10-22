#include "ZombieSpawner.h"

UZombieSpawner::UZombieSpawner()
{
	PrimaryComponentTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	Mesh->SetupAttachment(this);
}

void UZombieSpawner::Spawn()
{
	GetWorld()->SpawnActor<AActor>(ZombieToSpawn, Mesh->GetRelativeTransform(), FActorSpawnParameters());
}
