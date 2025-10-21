#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerWeaponComponent.generated.h"

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Data")
	TObjectPtr<UStaticMesh> WeaponMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Data")
	FName WeaponSocket = "";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Data")
	int WeaponDamage = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Data")
	int WeaponRange = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Data")
	int MaxAmmunition = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Data")
	int WeaponScore = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Data")
	float TimeBetweenShotInSeconds = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Data")
	float ReloadInterval = 0;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUnlimitedAmmoBonusSignature, bool, IsActive);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnKillScoredSignature, int, Score);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWeaponAmmoChangedSignature, int, CurrentAmmo, int, MaxAmmo);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TD_2_NICOLAS_CORBI_API UPlayerWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	int CurrentIndex = 0;

	bool isUnlimitedAmmo = false;

	TArray<int> WeaponsCurrentAmmo;
	TArray<float> WeaponsCurrentShotTimer;

	FTimerHandle Handle;

	TObjectPtr<UStaticMeshComponent> WeaponMeshComponent = nullptr;

protected:	
	UPlayerWeaponComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TArray<FWeaponData> WeaponDatas;

	void ReloadOneAmmo();

	void CancelUnlimitedAmmoBonus();

public:	
	UFUNCTION()
	void HandleShoot(FVector CameraLocation, FRotator CameraRotation);

	UFUNCTION()
	void SwitchWeapon(int index);

	UFUNCTION()
	void ReloadWeapon();

	UFUNCTION()
	void SetMesh(UStaticMeshComponent* mesh);

	UFUNCTION()
	void TriggerUnlimitedAmmoBonus(float duration);

	UPROPERTY(BlueprintAssignable, Category = "WeaponEvents")
	FOnUnlimitedAmmoBonusSignature OnUnlimitedAmmoBonus;

	UPROPERTY(BlueprintAssignable, Category = "WeaponEvents")
	FOnWeaponAmmoChangedSignature OnWeaponAmmoChanged;

	UPROPERTY(BlueprintAssignable, Category = "WeaponEvents")
	FOnKillScoredSignature OnKillScored;
};
