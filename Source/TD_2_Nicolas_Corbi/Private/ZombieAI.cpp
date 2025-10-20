#include "ZombieAI.h"
#include "Components/CapsuleComponent.h"
#include "PlayerHealthComponent.h"

AZombieAI::AZombieAI()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UPlayerHealthComponent>("Health Component");
}

void AZombieAI::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AZombieAI::OnHit);
}

void AZombieAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	InvicibilityTime += DeltaTime;
}

void AZombieAI::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UPlayerHealthComponent* PlayerHealthComponent = OtherActor->GetComponentByClass<UPlayerHealthComponent>();

	if (InvicibilityTime >= 0.7f && PlayerHealthComponent)
	{
		PlayerHealthComponent->TakeDamage(DamageToPlayer);

		InvicibilityTime = 0;
	}
}
