#include "MyPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "MyGameStateBase.h"
#include "MySaveGame.h"
#include "Kismet/GameplayStatics.h"

AMyPlayerController::AMyPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!MappingContext)
	{
		return;
	}

	if (ULocalPlayer* localPlayer = Cast<ULocalPlayer>(Player))
	{
		if (TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSystem = localPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			InputSystem->AddMappingContext(MappingContext, 0);
		}
	}

	MyChara = Cast<AMyCharacter>(GetPawn());

	MyChara->PlayerHealthComponent->OnHealthDepleted.AddUniqueDynamic(this, &AMyPlayerController::TriggerPlayerDeath);

	MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	MyGameInstance->Load();
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		for (FInputData data : InputDatas)
		{
			EnhancedInputComponent->BindAction(data.Action, data.TriggerType, this, data.ActionName);
		}
	}
}

void AMyPlayerController::Move(const FInputActionValue& Value)
{
	FVector MovementVector = Value.Get<FVector>();

	FRotator CameraRotation = FRotator(0.f, GetControlRotation().Yaw, 0.f);

	FVector RotatedVector = CameraRotation.RotateVector(MovementVector);

	GetPawn()->AddMovementInput(RotatedVector);
}

void AMyPlayerController::Look(const FInputActionValue& Value)
{
	FVector2D Values = Value.Get<FVector2D>();

	AddYawInput(Values.X * GetWorld()->GetDeltaSeconds() * CameraSensitivity);
	AddPitchInput(Values.Y * GetWorld()->GetDeltaSeconds() * CameraSensitivity);
}

void AMyPlayerController::Jump(const FInputActionValue& Value)
{
	if (MyChara)
	{
		MyChara->Jump();
	}
}

void AMyPlayerController::Shoot(const FInputActionValue& Value)
{
	if (MyChara)
	{
		MyChara->ForwardShoot();
	}
}

void AMyPlayerController::SwitchWeapon1(const FInputActionValue& Value)
{
	if (MyChara)
	{
		MyChara->ForwardSwitchWeapon(0);
	}
}

void AMyPlayerController::SwitchWeapon2(const FInputActionValue& Value)
{
	if (MyChara)
	{
		MyChara->ForwardSwitchWeapon(1);
	}
}

void AMyPlayerController::SwitchWeapon3(const FInputActionValue& Value)
{
	if (MyChara)
	{
		MyChara->ForwardSwitchWeapon(2);
	}
}

void AMyPlayerController::ReloadWeapon(const FInputActionValue& Value)
{
	if (MyChara)
	{
		MyChara->ForwardReloadWeapon();
	}
}

void AMyPlayerController::TriggerPlayerDeath()
{
	MyGameInstance->CustomSaveGame->LastDeathPosition = MyChara->GetActorLocation();

	MyGameInstance->CustomSaveGame->Leaderboards.Add("AAA - " + FString::FromInt(MyGameInstance->CustomSaveGame->TryNumber++), Cast<AMyGameStateBase>(UGameplayStatics::GetGameState(GetWorld()))->RetrieveScore());

	MyGameInstance->Save();

	OnTriggerPlayerDeath.Broadcast();
}
