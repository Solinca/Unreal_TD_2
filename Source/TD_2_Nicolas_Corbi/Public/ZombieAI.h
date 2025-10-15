#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ZombieAI.generated.h"

UCLASS()
class TD_2_NICOLAS_CORBI_API AZombieAI : public ACharacter
{
	GENERATED_BODY()

protected:
	AZombieAI();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	int DamageToPlayer;

private:
	float InvicibilityTime = 0.7f;

	// UFUNCTION()
	// void OnOverlapBegin(UPrimitiveComponent* OverlappingComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
