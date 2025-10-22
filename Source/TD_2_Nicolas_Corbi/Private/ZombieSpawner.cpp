#include "ZombieSpawner.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UZombieSpawner::UZombieSpawner()
{
	PrimaryComponentTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	Mesh->SetupAttachment(this);
}

void UZombieSpawner::Spawn()
{
	AActor* Zombie = GetWorld()->SpawnActor<AActor>(ZombieToSpawn, Mesh->GetRelativeTransform(), FActorSpawnParameters());

	Cast<ACharacter>(Zombie)->GetCharacterMovement()->MaxWalkSpeed = FMath::RandRange(MinZombieSpeed, MaxZombieSpeed);
}
