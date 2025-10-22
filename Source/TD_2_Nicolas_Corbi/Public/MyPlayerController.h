#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "MyCharacter.h"
#include "MyGameInstance.h"
#include "MyPlayerController.generated.h"

USTRUCT(BlueprintType)
struct FInputData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Data")
	TObjectPtr<UInputAction> Action = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Data")
	ETriggerEvent TriggerType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Data")
	FName ActionName;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTriggerPlayerDeathSignature);

UCLASS()
class TD_2_NICOLAS_CORBI_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	AMyPlayerController();
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Mapping")
	TObjectPtr<UInputMappingContext> MappingContext = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Data")
	TArray<FInputData> InputDatas;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Settings")
	float CameraSensitivity = 50.0f;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnTriggerPlayerDeathSignature OnTriggerPlayerDeath;

private:
	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void Look(const FInputActionValue& Value);

	UFUNCTION()
	void Jump(const FInputActionValue& Value);

	UFUNCTION()
	void Shoot(const FInputActionValue& Value);

	UFUNCTION()
	void SwitchWeapon1(const FInputActionValue& Value);

	UFUNCTION()
	void SwitchWeapon2(const FInputActionValue& Value);

	UFUNCTION()
	void SwitchWeapon3(const FInputActionValue& Value);

	UFUNCTION()
	void ReloadWeapon(const FInputActionValue& Value);

	UFUNCTION()
	void TriggerPlayerDeath();

	AMyCharacter* MyChara = nullptr;

	UMyGameInstance* MyGameInstance = nullptr;
};
