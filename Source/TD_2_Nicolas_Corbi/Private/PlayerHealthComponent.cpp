#include "PlayerHealthComponent.h"

UPlayerHealthComponent::UPlayerHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPlayerHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
}

int UPlayerHealthComponent::GetMaxHealth()
{
	return MaxHealth;
}

int UPlayerHealthComponent::GetCurrentHealth()
{
	return CurrentHealth;
}

void UPlayerHealthComponent::TakeDamage(int value)
{
	CurrentHealth -= value;

	CurrentHealth = FMath::Clamp(CurrentHealth, 0, MaxHealth);

	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);

	if (CurrentHealth == 0)
	{
		OnHealthDepleted.Broadcast();
	}
}

void UPlayerHealthComponent::HealHealth(int value)
{
	CurrentHealth += value;

	CurrentHealth = FMath::Clamp(CurrentHealth, 0, MaxHealth);

	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
}
