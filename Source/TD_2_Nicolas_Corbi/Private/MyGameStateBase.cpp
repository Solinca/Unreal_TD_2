#include "MyGameStateBase.h"

void AMyGameStateBase::GainScore(int amount)
{
	SCORE += amount;

	OnScoreGained.Broadcast(SCORE);
}

void AMyGameStateBase::GainMoney(int amount)
{
	MONEY += amount;

	OnMoneyGained.Broadcast(MONEY);
}

int AMyGameStateBase::RetrieveScore()
{
	return SCORE;
}

int AMyGameStateBase::RetrieveMoney()
{
	return MONEY;
}
