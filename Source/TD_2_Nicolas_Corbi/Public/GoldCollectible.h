#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoldCollectible.generated.h"

UCLASS()
class TD_2_NICOLAS_CORBI_API AGoldCollectible : public AActor
{
	GENERATED_BODY()
	
protected:
	AGoldCollectible();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Mesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	int GoldGainAmount = 0;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappingComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
