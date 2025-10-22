#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <ZombieSpawner.h>
#include "ZombieWaveManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewWaveSignature, int, WaveNumber);

UCLASS()
class TD_2_NICOLAS_CORBI_API AZombieWaveManager : public AActor
{
	GENERATED_BODY()

private:
	FTimerHandle Handle;

	int CurrentZombieNumberToSpawn = 0;

	int SpawnedZombieNumber = 0;

	int WaveNumber = 0;

	int CurrentZombieKilled = 0;

protected:
	AZombieWaveManager();
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TArray<TObjectPtr<UZombieSpawner>> ZombieSpawnerList;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	int ZombieNumberPerWave = 3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	float DelayBetweenSpawn = 1.5f;

	UFUNCTION()
	void Spawn();

	UFUNCTION()
	void NewWave();

	UFUNCTION()
	void ZombieKilledCount(int _);

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnNewWaveSignature OnNewWave;
};
