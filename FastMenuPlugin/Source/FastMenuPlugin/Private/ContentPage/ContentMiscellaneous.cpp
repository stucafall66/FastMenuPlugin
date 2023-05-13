// Fill out your copyright notice in the Description page of Project Settings.


#include "ContentPage/ContentMiscellaneous.h"
#include "Components/ComboBoxKey.h"
#include "Components/CheckBox.h"
#include "ContentPage/FastMenuComboBoxKey.h"
#include "Kismet/GameplayStatics.h"
#include "FastMenuSaveGame.h"
#include "SettingStructures.h"
#include "Kismet/KismetInternationalizationLibrary.h"


void UContentMiscellaneous::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (Language_FastMenuComboBoxKey)
	{
		Language_FastMenuComboBoxKey->OnSelectionChanged.AddDynamic(this, &ThisClass::OnLanguageChange);
	}

	SetupComboBoxes();

	// Load Saved Game
	UFastMenuSaveGame* CurrentSaveGame = Cast<UFastMenuSaveGame>(UGameplayStatics::LoadGameFromSlot(FString("FastMenuSaveGameSlot"), 0));
	if (CurrentSaveGame != nullptr)
	{
		FMiscellaneousContentSettings CurrentMiscellaneousContentSetting = CurrentSaveGame->GetSavedMiscellaneousSettings();
		if (Language_FastMenuComboBoxKey)
		{
			Language = CurrentMiscellaneousContentSetting.Language;
			if (Language == EComboBoxOption::English)
			{
				Language_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "English", "English").ToString()));
			}
			if (Language == EComboBoxOption::Chinese)
			{
				Language_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Chinese", "Chinese").ToString()));
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CurrentSaveGame is nullptr"));
	}
}

void UContentMiscellaneous::ApplyChanges()
{
	Super::ApplyChanges();

	// Run command for each setting, then save settings to savegame object
	APlayerController* OwningPlayer = GetOwningPlayer();
	if (OwningPlayer)
	{
		if (Language == EComboBoxOption::English)
		{
			FString Culture = FString("en");
			if (!UKismetInternationalizationLibrary::SetCurrentCulture(Culture, true))
			{
				UE_LOG(LogTemp, Warning, TEXT("Set Culture to EN Failed"));
			}
		}
		if (Language == EComboBoxOption::Chinese)
		{
			FString Culture = FString("zh-CN");
			if (!UKismetInternationalizationLibrary::SetCurrentCulture(Culture, true))
			{
				UE_LOG(LogTemp, Warning, TEXT("Set Culture to ZH Failed"));
			}
		}
	}
	//Save Settings to File
	SaveChanges();
}

void UContentMiscellaneous::OnLanguageChange(FName SelectedItem, ESelectInfo::Type SelectionType)
{
	if (SelectedItem == FName(*NSLOCTEXT("FastMenuPlugin", "English", "English").ToString()))
	{
		Language = EComboBoxOption::English;
	}
	if (SelectedItem == FName(*NSLOCTEXT("FastMenuPlugin", "Chinese", "Chinese").ToString()))
	{
		Language = EComboBoxOption::Chinese;
	}
}

void UContentMiscellaneous::SaveChanges()
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

	FMiscellaneousContentSettings CurrentMiscellaneousContentSettings = FMiscellaneousContentSettings{ Language };
	if (CurrentSaveGame != nullptr)
	{
		CurrentSaveGame->SetSavedMiscellaneousSettings(CurrentMiscellaneousContentSettings);
		bool Success = UGameplayStatics::SaveGameToSlot(CurrentSaveGame, FString("FastMenuSaveGameSlot"), 0);
		if (!Success)
		{
			UE_LOG(LogTemp, Warning, TEXT("Save Game to Slot Failed"));
		}
	}
}

void UContentMiscellaneous::SetupComboBoxes()
{
	if (Language_FastMenuComboBoxKey)
	{
		Language_FastMenuComboBoxKey->AddOption(FName(*NSLOCTEXT("FastMenuPlugin", "English", "English").ToString()));
		Language_FastMenuComboBoxKey->AddOption(FName(*NSLOCTEXT("FastMenuPlugin", "Chinese", "Chinese").ToString()));
		Language_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "English", "English").ToString()));
	}
}

void UContentMiscellaneous::RestoreDefault()
{
	FMiscellaneousContentSettings DefaultMiscellaneousContentSettings;
	if (Language_FastMenuComboBoxKey)
	{
		switch (DefaultMiscellaneousContentSettings.Language)
		{
		case EComboBoxOption::English:
			Language_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "English", "English").ToString()));
			break;
		case EComboBoxOption::Chinese:
			Language_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Chinese", "Chinese").ToString()));
			break;
		default:
			break;
		}
	}
}
