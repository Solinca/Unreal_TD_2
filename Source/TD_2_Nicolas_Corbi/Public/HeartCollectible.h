#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HeartCollectible.generated.h"

UCLASS()
class TD_2_NICOLAS_CORBI_API AHeartCollectible : public AActor
{
	GENERATED_BODY()
	
protected:
	AHeartCollectible();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> Mesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	int HealthRestoreAmount = 0;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappingComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
