#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerHealthComponent.h"
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	float MaxInvicibilityTime = 0.7f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UPlayerHealthComponent> HealthComponent;

private:
	float InvicibilityTime = MaxInvicibilityTime;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
