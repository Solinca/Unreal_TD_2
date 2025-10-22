#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreGainedSignature, int, Score);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMoneyGainedSignature, int, Money);

UCLASS()
class TD_2_NICOLAS_CORBI_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

private:
	int SCORE = 0;
	int MONEY = 0;

public:
	UFUNCTION()
	void GainScore(int amount);
	
	UFUNCTION()
	void GainMoney(int money);

	UFUNCTION()
	int RetrieveScore();

	UFUNCTION()
	int RetrieveMoney();

	UPROPERTY(BlueprintAssignable, Category = "Global Events")
	FOnScoreGainedSignature OnScoreGained;

	UPROPERTY(BlueprintAssignable, Category = "Global Events")
	FOnMoneyGainedSignature OnMoneyGained;
};
