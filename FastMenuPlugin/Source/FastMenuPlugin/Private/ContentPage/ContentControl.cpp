// Fill out your copyright notice in the Description page of Project Settings.


#include "ContentPage/ContentControl.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "FastMenuSaveGame.h"
#include "Components/TextBlock.h"


void UContentControl::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// Load Saved Game
	UFastMenuSaveGame* CurrentSaveGame = Cast<UFastMenuSaveGame>(UGameplayStatics::LoadGameFromSlot(FString("FastMenuSaveGameSlot"), 0));
	if (CurrentSaveGame != nullptr)
	{
		FControlContentSettings CurrentControlContentSetting = CurrentSaveGame->GetSavedControlSettings();

		if (SetDestinationKeyText)
		{
			SetDestinationKeyText->SetText(CurrentControlContentSetting.SetDestinationKey.GetInputText());
			CurrentSetDestinationKey = CurrentControlContentSetting.SetDestinationKey;
		}
		if (ForwardKeyText)
		{
			ForwardKeyText->SetText(CurrentControlContentSetting.ForwardKey.GetInputText());
			CurrentForwardKey = CurrentControlContentSetting.ForwardKey;
		}
		if (BackwardKeyText)
		{
			BackwardKeyText->SetText(CurrentControlContentSetting.BackwardKey.GetInputText());
			CurrentBackwardKey = CurrentControlContentSetting.BackwardKey;
		}
		if (LeftKeyText)
		{
			LeftKeyText->SetText(CurrentControlContentSetting.LeftKey.GetInputText());
			CurrentLeftKey = CurrentControlContentSetting.LeftKey; 
		}
		if (RightKeyText)
		{
			RightKeyText->SetText(CurrentControlContentSetting.RightKey.GetInputText());
			CurrentRightKey = CurrentControlContentSetting.RightKey;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CurrentSaveGame is nullptr"));
	}
	SetInputKeySelected();
}

void UContentControl::ApplyChanges()
{
	ProcessInputKeyPanels();
	// Apply input changes, then save settings to savegame object
	UInputSettings* InputSettings =  UInputSettings::GetInputSettings();
	if (InputSettings != nullptr)
	{
		TArray<FInputActionKeyMapping> InputActionKeyMappingsSetDestination;
		InputSettings->GetActionMappingByName(FName("SetDestination"), InputActionKeyMappingsSetDestination);
		for (FInputActionKeyMapping InputActionKeyMapping : InputActionKeyMappingsSetDestination)
		{
			InputSettings->RemoveActionMapping(InputActionKeyMapping);
		}
		//
		TArray<FInputActionKeyMapping> InputActionKeyMappingsForward;
		InputSettings->GetActionMappingByName(FName("Forward"), InputActionKeyMappingsForward);
		for (FInputActionKeyMapping InputActionKeyMapping : InputActionKeyMappingsForward)
		{
			InputSettings->RemoveActionMapping(InputActionKeyMapping);
		}
		//
		TArray<FInputActionKeyMapping> InputActionKeyMappingsBackward;
		InputSettings->GetActionMappingByName(FName("Backward"), InputActionKeyMappingsBackward);
		for (FInputActionKeyMapping InputActionKeyMapping : InputActionKeyMappingsBackward)
		{
			InputSettings->RemoveActionMapping(InputActionKeyMapping);
		}
		//
		TArray<FInputActionKeyMapping> InputActionKeyMappingsLeft;
		InputSettings->GetActionMappingByName(FName("Left"), InputActionKeyMappingsLeft);
		for (FInputActionKeyMapping InputActionKeyMapping : InputActionKeyMappingsLeft)
		{
			InputSettings->RemoveActionMapping(InputActionKeyMapping);
		}
		//
		TArray<FInputActionKeyMapping> InputActionKeyMappingsRight;
		InputSettings->GetActionMappingByName(FName("Right"), InputActionKeyMappingsRight);
		for (FInputActionKeyMapping InputActionKeyMapping : InputActionKeyMappingsRight)
		{
			InputSettings->RemoveActionMapping(InputActionKeyMapping);
		}
		
		//Add the new key binding
		UE_LOG(LogTemp, Warning, TEXT("CurrentSetDestinationKey.Key is %s"), *CurrentSetDestinationKey.Key.GetFName().ToString());
		FInputActionKeyMapping SetDestinationKeyMapping(
			FName("SetDestination"), 
			CurrentSetDestinationKey.Key,
			CurrentSetDestinationKey.bShift,
			CurrentSetDestinationKey.bCtrl,
			CurrentSetDestinationKey.bAlt,
			CurrentSetDestinationKey.bCmd
		);
		InputSettings->AddActionMapping(SetDestinationKeyMapping, true);
		//
		FInputActionKeyMapping ForwardKeyMapping(
			FName("Forward"),
			CurrentForwardKey.Key,
			CurrentForwardKey.bShift,
			CurrentForwardKey.bCtrl,
			CurrentForwardKey.bAlt,
			CurrentForwardKey.bCmd
		);
		InputSettings->AddActionMapping(ForwardKeyMapping, true);
		//
		FInputActionKeyMapping BackwardKeyMapping(
			FName("Backward"),
			CurrentBackwardKey.Key,
			CurrentBackwardKey.bShift,
			CurrentBackwardKey.bCtrl,
			CurrentBackwardKey.bAlt,
			CurrentBackwardKey.bCmd
		);
		InputSettings->AddActionMapping(BackwardKeyMapping, true);
		//
		FInputActionKeyMapping LeftKeyMapping(
			FName("Left"),
			CurrentLeftKey.Key,
			CurrentLeftKey.bShift,
			CurrentLeftKey.bCtrl,
			CurrentLeftKey.bAlt,
			CurrentLeftKey.bCmd
		);
		InputSettings->AddActionMapping(LeftKeyMapping, true);
		//
		FInputActionKeyMapping RightKeyMapping(
			FName("Right"),
			CurrentRightKey.Key,
			CurrentRightKey.bShift,
			CurrentRightKey.bCtrl,
			CurrentRightKey.bAlt,
			CurrentRightKey.bCmd
		);
		InputSettings->AddActionMapping(RightKeyMapping, true);
	}
	SaveChanges();
}

void UContentControl::SaveChanges()
{
	UFastMenuSaveGame* CurrentSaveGame = nullptr;
	if (UGameplayStatics::DoesSaveGameExist(FString("FastMenuSaveGameSlot"), 0))
	{
		CurrentSaveGame = Cast<UFastMenuSaveGame>(UGameplayStatics::LoadGameFromSlot(FString("FastMenuSaveGameSlot"), 0));
	}
	else
	{
		CurrentSaveGame = Cast<UFastMenuSaveGame>(UGameplayStatics::CreateSaveGameObject(UFastMenuSaveGame::StaticClass()));
	}

	FControlContentSettings CurrentControlContentSettings = FControlContentSettings{ CurrentSetDestinationKey, CurrentForwardKey, CurrentBackwardKey, CurrentLeftKey, CurrentRightKey };
	if (CurrentSaveGame != nullptr)
	{
		CurrentSaveGame->SetSavedControlSettings(CurrentControlContentSettings);
		//UE_LOG(LogTemp, Warning, TEXT("In contentvideo.cpp, VideoResolution is %s"), *CurrentSaveGame->GetSavedVideoSettings().VideoResolution.ToString());
		bool Success = UGameplayStatics::SaveGameToSlot(CurrentSaveGame, FString("FastMenuSaveGameSlot"), 0);
		if (!Success)
		{
			UE_LOG(LogTemp, Warning, TEXT("Save Game to Slot Failed"));
		}
	}
}

FControlContentSettings UContentControl::GetDefaultKeySettings()
{
	return FControlContentSettings();
}

void UContentControl::RestoreDefault()
{

}
