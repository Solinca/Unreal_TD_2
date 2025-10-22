#include "ZombieWaveManager.h"
#include "Kismet/GameplayStatics.h"
#include <MyGameStateBase.h>

AZombieWaveManager::AZombieWaveManager()
{
	PrimaryActorTick.bCanEverTick = false;

	ZombieSpawnerList.Push(CreateDefaultSubobject<UZombieSpawner>("Spawner 1"));
	ZombieSpawnerList.Push(CreateDefaultSubobject<UZombieSpawner>("Spawner 2"));
	ZombieSpawnerList.Push(CreateDefaultSubobject<UZombieSpawner>("Spawner 3"));
}

void AZombieWaveManager::BeginPlay()
{
	Super::BeginPlay();

	Cast<AMyGameStateBase>(UGameplayStatics::GetGameState(GetWorld()))->OnScoreGained.AddUniqueDynamic(this, &AZombieWaveManager::ZombieKilledCount);

	NewWave();
}

void AZombieWaveManager::Spawn()
{
	if (SpawnedZombieNumber == CurrentZombieNumberToSpawn)
	{
		GetWorld()->GetTimerManager().ClearTimer(Handle);

		return;
	}

	for (TObjectPtr<UZombieSpawner> Spawner : ZombieSpawnerList)
	{
		Spawner->Spawn();
	}

	SpawnedZombieNumber++;
}

void AZombieWaveManager::NewWave()
{
	WaveNumber++;

	OnNewWave.Broadcast(WaveNumber);

	CurrentZombieNumberToSpawn += ZombieNumberPerWave;

	SpawnedZombieNumber = 0;
	CurrentZombieKilled = 0;

	GetWorld()->GetTimerManager().SetTimer(Handle, this, &AZombieWaveManager::Spawn, DelayBetweenSpawn, true);
}

void AZombieWaveManager::ZombieKilledCount(int _)
{
	CurrentZombieKilled++;

	if (CurrentZombieKilled == CurrentZombieNumberToSpawn * ZombieSpawnerList.Num())
	{
		NewWave();
	}
}
