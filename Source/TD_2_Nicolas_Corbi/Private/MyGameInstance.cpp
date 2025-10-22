#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UMyGameInstance::Load()
{
	if (UGameplayStatics::DoesSaveGameExist("Slot", 0))
	{
		FAsyncLoadGameFromSlotDelegate LoadDelegate;

		LoadDelegate.BindUObject(this, &UMyGameInstance::LoadGameFinished);

		UGameplayStatics::AsyncLoadGameFromSlot("Slot", 0, LoadDelegate);
	}
	else
	{
		CustomSaveGame = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	}
}

void UMyGameInstance::Save()
{
	FAsyncSaveGameToSlotDelegate SaveDelegate;

	SaveDelegate.BindUObject(this, &UMyGameInstance::SaveGameFinished);

	UGameplayStatics::AsyncSaveGameToSlot(CustomSaveGame, "Slot", 0, SaveDelegate);
}

void UMyGameInstance::LoadGameFinished(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData)
{
	CustomSaveGame = Cast<UMySaveGame>(LoadedGameData);

	OnLoadFinished.Broadcast(CustomSaveGame);
}

void UMyGameInstance::SaveGameFinished(const FString& SlotName, const int32 UserIndex, bool Succeed)
{
	OnSaveFinished.Broadcast();
}
