#include "PlayerRemainingSoul.h"
#include "MyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameStateBase.h"
#include "MyGameInstance.h"

APlayerRemainingSoul::APlayerRemainingSoul()
{
	PrimaryActorTick.bCanEverTick = false;

	Box = CreateDefaultSubobject<UBoxComponent>("Box");

	Box->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	Mesh->SetupAttachment(Box);

	Box->OnComponentBeginOverlap.AddDynamic(this, &APlayerRemainingSoul::OnOverlapBegin);
}

void APlayerRemainingSoul::BeginPlay()
{
	Super::BeginPlay();

	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (MyGameInstance->CustomSaveGame->LastDeathPosition == FVector::Zero())
	{
		Box->SetVisibility(false, true);
		Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else
	{
		SetActorLocation(MyGameInstance->CustomSaveGame->LastDeathPosition);
	}
}

void APlayerRemainingSoul::OnOverlapBegin(UPrimitiveComponent* OverlappingComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "GNENEE");

	if (Cast<AMyCharacter>(OtherActor))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "HIT");

		Cast<AMyGameStateBase>(UGameplayStatics::GetGameState(GetWorld()))->GainMoney(GoldGainAmount);

		Box->SetVisibility(false, true);
		Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}
