#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

UCLASS()
class TD_2_NICOLAS_CORBI_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Save")
	FVector LastDeathPosition;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Save")
	TMap<FString, int> Leaderboards;
};
