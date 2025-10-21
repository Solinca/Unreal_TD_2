#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BonusCollectible.generated.h"

UCLASS()
class TD_2_NICOLAS_CORBI_API ABonusCollectible : public AActor
{
	GENERATED_BODY()
	
protected:
	ABonusCollectible();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Mesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	float Duration;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappingComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
