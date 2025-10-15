#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerHealthComponent.h"
#include "PlayerWeaponComponent.h"
#include "MyCharacter.generated.h"

UCLASS()
class TD_2_NICOLAS_CORBI_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	AMyCharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArm = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCameraComponent> Camera = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UPlayerHealthComponent> PlayerHealthComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UPlayerWeaponComponent> PlayerWeaponComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> PlayerWeaponMesh = nullptr;

public:
	UFUNCTION()
	void ForwardShoot();

	UFUNCTION()
	void ForwardSwitchWeapon(int index);

	UFUNCTION()
	void ForwardReloadWeapon();
};
