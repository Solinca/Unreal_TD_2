#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ZombieAIController.generated.h"

UCLASS()
class TD_2_NICOLAS_CORBI_API AZombieAIController : public AAIController
{
	GENERATED_BODY()

private:
	ACharacter* Player;
	
protected:
	AZombieAIController();
};
