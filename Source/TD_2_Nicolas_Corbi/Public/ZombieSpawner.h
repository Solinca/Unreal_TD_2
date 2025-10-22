#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ZombieSpawner.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TD_2_NICOLAS_CORBI_API UZombieSpawner : public USceneComponent
{
	GENERATED_BODY()

protected:
	UZombieSpawner();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Mesh;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	TSubclassOf<AActor> ZombieToSpawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	int MinZombieSpeed = 500;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	int MaxZombieSpeed = 800;

	UFUNCTION()
	void Spawn();
};
