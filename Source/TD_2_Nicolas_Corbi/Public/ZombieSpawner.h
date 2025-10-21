#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZombieSpawner.generated.h"

UCLASS()
class TD_2_NICOLAS_CORBI_API AZombieSpawner : public AActor
{
	GENERATED_BODY()

protected:
	AZombieSpawner();
	virtual void BeginPlay() override;

	UFUNCTION()
	void Spawn();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TSubclassOf<AActor> ZombieToSpawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	float DelayBetweenSpawn = 3.0f;
};
