#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

class UMySaveGame;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSaveFinishedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoadFinishedSignature, UMySaveGame*, MySaveGame);

UCLASS()
class TD_2_NICOLAS_CORBI_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Load();

	UFUNCTION(BlueprintCallable)
	void Save();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Save")
	TObjectPtr<UMySaveGame> CustomSaveGame = nullptr;

	UPROPERTY(BlueprintAssignable)
	FOnSaveFinishedSignature OnSaveFinished;

	UPROPERTY(BlueprintAssignable)
	FOnLoadFinishedSignature OnLoadFinished;

private:
	UFUNCTION()
	void LoadGameFinished(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData);
	UFUNCTION()
	void SaveGameFinished(const FString& SlotName, const int32 UserIndex, bool Succeed);
};
