#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthDepletedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, int, CurrentHealth, int, MaxHealth);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TD_2_NICOLAS_CORBI_API UPlayerHealthComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	int CurrentHealth;

protected:
	UPlayerHealthComponent();
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	int MaxHealth;

public:
	UFUNCTION(BlueprintCallable)
	int GetMaxHealth();

	UFUNCTION(BlueprintCallable)
	int GetCurrentHealth();

	UFUNCTION(BlueprintCallable)
	void TakeDamage(int value);

	UFUNCTION(BlueprintCallable)
	void HealHealth(int value);

	UPROPERTY(BlueprintAssignable, Category = "HealthEvents")
	FOnHealthDepletedSignature OnHealthDepleted;

	UPROPERTY(BlueprintAssignable, Category = "HealthEvents")
	FOnHealthChangedSignature OnHealthChanged;
};
