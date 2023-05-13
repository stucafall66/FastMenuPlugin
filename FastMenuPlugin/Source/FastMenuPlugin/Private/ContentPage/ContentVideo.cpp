// Fill out your copyright notice in the Description page of Project Settings.


#include "ContentPage/ContentVideo.h"
#include "Components/ComboBoxKey.h"
#include "Components/CheckBox.h"
#include "ContentPage/FastMenuComboBoxKey.h"
#include "Kismet/GameplayStatics.h"
#include "FastMenuSaveGame.h"
#include "SettingStructures.h"
#include "GameFramework/GameUserSettings.h"
// #include "GenericPlatform/GenericWindow.h"

void UContentVideo::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	UE_LOG(LogTemp, Warning, TEXT("NativeOnInitialized"));

	if (VideoResolution_FastMenuComboBoxKey)
	{
		VideoResolution_FastMenuComboBoxKey->OnSelectionChanged.AddDynamic(this, &ThisClass::OnVideoResolutionChange);
	}
	if (Fullscreen_CheckBox)
	{
		Fullscreen_CheckBox->OnCheckStateChanged.AddDynamic(this, &ThisClass::OnFullscreenChange);
	}
	if (ShadowQuality_FastMenuComboBoxKey)
	{
		ShadowQuality_FastMenuComboBoxKey->OnSelectionChanged.AddDynamic(this, &ThisClass::OnShadowQualityChange);
	}
	if (PostProcessing_FastMenuComboBoxKey)
	{
		PostProcessing_FastMenuComboBoxKey->OnSelectionChanged.AddDynamic(this, &ThisClass::OnPostProcessingChange);
	}
	if (TextureQuality_FastMenuComboBoxKey)
	{
		TextureQuality_FastMenuComboBoxKey->OnSelectionChanged.AddDynamic(this, &ThisClass::OnTextureQualityChange);
	}
	if (MaterialQuality_FastMenuComboBoxKey)
	{
		MaterialQuality_FastMenuComboBoxKey->OnSelectionChanged.AddDynamic(this, &ThisClass::OnMaterialQualityChange);
	}
	if (AntiAliasing_FastMenuComboBoxKey)
	{
		AntiAliasing_FastMenuComboBoxKey->OnSelectionChanged.AddDynamic(this, &ThisClass::OnAntiAliasingChange);
	}
	if (Effect_FastMenuComboBoxKey)
	{
		Effect_FastMenuComboBoxKey->OnSelectionChanged.AddDynamic(this, &ThisClass::OnEffectChange);
	}
	if (DetailMode_FastMenuComboBoxKey)
	{
		DetailMode_FastMenuComboBoxKey->OnSelectionChanged.AddDynamic(this, &ThisClass::OnDetailModeChange);
	}
	if (ViewDistance_FastMenuComboBoxKey)
	{
		ViewDistance_FastMenuComboBoxKey->OnSelectionChanged.AddDynamic(this, &ThisClass::OnViewDistanceChange);
	}

	SetupComboBoxes();
	
	// Load Saved Game
	UFastMenuSaveGame* CurrentSaveGame = Cast<UFastMenuSaveGame>(UGameplayStatics::LoadGameFromSlot(FString("FastMenuSaveGameSlot"), 0));
	if (CurrentSaveGame != nullptr)
	{
		FVideoContentSettings CurrentVideoContentSetting = CurrentSaveGame->GetSavedVideoSettings();
		if (VideoResolution_FastMenuComboBoxKey)
		{
			VideoResolution_FastMenuComboBoxKey->SetSelectedOption(CurrentVideoContentSetting.VideoResolution);
			VideoResolution = CurrentVideoContentSetting.VideoResolution;
		}
		if (Fullscreen_CheckBox)
		{
			if (CurrentVideoContentSetting.Fullscreen)
			{
				Fullscreen_CheckBox->SetCheckedState(ECheckBoxState::Checked);
			}
			else
			{
				Fullscreen_CheckBox->SetCheckedState(ECheckBoxState::Unchecked);
			}
			Fullscreen = CurrentVideoContentSetting.Fullscreen;
		}
		if (ShadowQuality_FastMenuComboBoxKey)
		{
			switch (CurrentVideoContentSetting.ShadowQuality)
			{
			case EComboBoxOption::Low:
				ShadowQuality_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Low", "Low").ToString()));
				break;
			case EComboBoxOption::Medium:
				ShadowQuality_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Medium", "Medium").ToString()));
				break;
			case EComboBoxOption::High:
				ShadowQuality_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "High", "High").ToString()));
				break;
			case EComboBoxOption::Epic:
				ShadowQuality_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Epic", "Epic").ToString()));
				break;
			default:
				break;
			}
			ShadowQuality = CurrentVideoContentSetting.ShadowQuality;
		}
		if (PostProcessing_FastMenuComboBoxKey)
		{
			switch (CurrentVideoContentSetting.PostProcessing)
			{
			case EComboBoxOption::Low:
				PostProcessing_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Low", "Low").ToString()));
				break;
			case EComboBoxOption::Medium:
				PostProcessing_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Medium", "Medium").ToString()));
				break;
			case EComboBoxOption::High:
				PostProcessing_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "High", "High").ToString()));
				break;
			case EComboBoxOption::Epic:
				PostProcessing_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Epic", "Epic").ToString()));
				break;
			default:
				break;
			}
			PostProcessing = CurrentVideoContentSetting.PostProcessing;
		}
		if (TextureQuality_FastMenuComboBoxKey)
		{
			switch (CurrentVideoContentSetting.TextureQuality)
			{
			case EComboBoxOption::Low:
				TextureQuality_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Low", "Low").ToString()));
				break;
			case EComboBoxOption::Medium:
				TextureQuality_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Medium", "Medium").ToString()));
				break;
			case EComboBoxOption::High:
				TextureQuality_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "High", "High").ToString()));
				break;
			case EComboBoxOption::Epic:
				TextureQuality_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Epic", "Epic").ToString()));
				break;
			default:
				break;
			}
			TextureQuality = CurrentVideoContentSetting.TextureQuality;
		}
		if (MaterialQuality_FastMenuComboBoxKey)
		{
			switch (CurrentVideoContentSetting.MaterialQuality)
			{
			case EComboBoxOption::Low:
				MaterialQuality_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Low", "Low").ToString()));
				break;
			case EComboBoxOption::Medium:
				MaterialQuality_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Medium", "Medium").ToString()));
				break;
			case EComboBoxOption::High:
				MaterialQuality_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "High", "High").ToString()));
				break;
			case EComboBoxOption::Epic:
				MaterialQuality_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Epic", "Epic").ToString()));
				break;
			default:
				break;
			}
			MaterialQuality = CurrentVideoContentSetting.MaterialQuality;
		}
		if (AntiAliasing_FastMenuComboBoxKey)
		{
			switch (CurrentVideoContentSetting.AntiAliasing)
			{
			case EComboBoxOption::Low:
				AntiAliasing_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Low", "Low").ToString()));
				break;
			case EComboBoxOption::Medium:
				AntiAliasing_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Medium", "Medium").ToString()));
				break;
			case EComboBoxOption::High:
				AntiAliasing_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "High", "High").ToString()));
				break;
			case EComboBoxOption::Epic:
				AntiAliasing_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Epic", "Epic").ToString()));
				break;
			default:
				break;
			}
			AntiAliasing = CurrentVideoContentSetting.AntiAliasing;
		}
		if (Effect_FastMenuComboBoxKey)
		{
			switch (CurrentVideoContentSetting.Effect)
			{
			case EComboBoxOption::Low:
				Effect_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Low", "Low").ToString()));
				break;
			case EComboBoxOption::Medium:
				Effect_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Medium", "Medium").ToString()));
				break;
			case EComboBoxOption::High:
				Effect_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "High", "High").ToString()));
				break;
			case EComboBoxOption::Epic:
				Effect_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Epic", "Epic").ToString()));
				break;
			default:
				break;
			}
			Effect = CurrentVideoContentSetting.Effect;
		}
		if (DetailMode_FastMenuComboBoxKey)
		{
			switch (CurrentVideoContentSetting.DetailMode)
			{
			case EComboBoxOption::Low:
				DetailMode_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Low", "Low").ToString()));
				break;
			case EComboBoxOption::Medium:
				DetailMode_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Medium", "Medium").ToString()));
				break;
			case EComboBoxOption::High:
				DetailMode_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "High", "High").ToString()));
				break;
			case EComboBoxOption::Epic:
				DetailMode_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Epic", "Epic").ToString()));
				break;
			default:
				break;
			}
			DetailMode = CurrentVideoContentSetting.DetailMode;
		}
		if (ViewDistance_FastMenuComboBoxKey)
		{
			switch (CurrentVideoContentSetting.ViewDistance)
			{
			case EComboBoxOption::Short:
				ViewDistance_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Short", "Short").ToString()));
				break;
			case EComboBoxOption::Medium:
				ViewDistance_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Medium", "Medium").ToString()));
				break;
			case EComboBoxOption::Long:
				ViewDistance_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Long", "Long").ToString()));
				break;
			default:
				break;
			}
			ViewDistance = CurrentVideoContentSetting.ViewDistance;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CurrentSaveGame is nullptr"));
	}
}

void UContentVideo::OnVideoResolutionChange(FName SelectedItem, ESelectInfo::Type SelectionType)
{
	VideoResolution = SelectedItem;
}

void UContentVideo::OnFullscreenChange(bool bIsChecked)
{
	Fullscreen = bIsChecked;
}

void UContentVideo::OnShadowQualityChange(FName SelectedItem, ESelectInfo::Type SelectionType)
{
	if (SelectedItem == FName(*NSLOCTEXT("FastMenuPlugin", "Low", "Low").ToString()))
	{
		ShadowQuality = EComboBoxOption::Low;
	}
	if (SelectedItem == FName(*NSLOCTEXT("FastMenuPlugin", "Medium", "Medium").ToString()))
	{
		ShadowQuality = EComboBoxOption::Medium;
	}
	if (SelectedItem == FName(*NSLOCTEXT("FastMenuPlugin", "High", "High").ToString()))
	{
		ShadowQuality = EComboBoxOption::High;
	}
	if (SelectedItem == FName(*NSLOCTEXT("FastMenuPlugin", "Epic", "Epic").ToString()))
	{
		ShadowQuality = EComboBoxOption::Epic;
	}
}

void UContentVideo::OnPostProcessingChange(FName SelectedItem, ESelectInfo::Type SelectionType)
{
	if (SelectedItem == FName(*NSLOCTEXT("FastMenuPlugin", "Low", "Low").ToString()))
	{
		PostProcessing = EComboBoxOption::Low;
	}
	if (SelectedItem == FName(*NSLOCTEXT("FastMenuPlugin", "Medium", "Medium").ToString()))
	{
		PostProcessing = EComboBoxOption::Medium;
	}
	if (SelectedItem == FName(*NSLOCTEXT("FastMenuPlugin", "High", "High").ToString()))
	{
		PostProcessing = EComboBoxOption::High;
	}
	if (SelectedItem == FName(*NSLOCTEXT("FastMenuPlugin", "Epic", "Epic").ToString()))
	{
		PostProcessing = EComboBoxOption::Epic;
	}
}

void UContentVideo::OnTextureQualityChange(FName SelectedItem, ESelectInfo::Type SelectionType)
{
	if (SelectedItem == FName(*NSLOCTEXT("FastMenuPlugin", "Low", "Low").ToString()))
	{
		TextureQuality = EComboBoxOption::Low;
	}
	if (SelectedItem == FName(*NSLOCTEXT("FastMenuPlugin", "Medium", "Medium").ToString()))
	{
		TextureQuality = EComboBoxOption::Medium;
	}
	if (SelectedItem == FName(*NSLOCTEXT("FastMenuPlugin", "High", "High").ToString()))
	{
		TextureQuality = EComboBoxOption::High;
	}
	if (SelectedItem == FName(*NSLOCTEXT("FastMenuPlugin", "Epic", "Epic").ToString()))
	{
		TextureQuality = EComboBoxOption::Epic;
	}
}

void UContentVideo::OnMaterialQualityChange(FName SelectedItem, ESelectInfo::Type SelectionType)
{
	if (SelectedItem == FName(*NSLOCTEXT("FastMenuPlugin", "Low", "Low").ToString()))
	{
		MaterialQuality = EComboBoxOption::Low;
	}
	if (SelectedItem == FName(*NSLOCTEXT("FastMenuPlugin", "Medium", "Medium").ToString()))
	{
		MaterialQuality = EComboBoxOption::Medium;
	}
	if (SelectedItem == FName(*NSLOCTEXT("FastMenuPlugin", "High", "High").ToString()))
	{
		MaterialQuality = EComboBoxOption::High;
	}
	if (SelectedItem == FName(*NSLOCTEXT("FastMenuPlugin", "Epic", "Epic").ToString()))
	{
		MaterialQuality = EComboBoxOption::Epic;
	}
}

void UContentVideo::OnAntiAliasingChange(FName SelectedItem, ESelectInfo::Type SelectionType)
{
	if (SelectedItem == FName(*NSLOCTEXT("FastMenuPlugin", "Low", "Low").ToString()))
	{
		AntiAliasing = EComboBoxOption::Low;
	}
	if (SelectedItem == FName(*NSLOCTEXT("FastMenuPlugin", "Medium", "Medium").ToString()))
	{
		AntiAliasing = EComboBoxOption::Medium;
	}
	if (SelectedItem == FName(*NSLOCTEXT("FastMenuPlugin", "High", "High").ToString()))
	{
		AntiAliasing = EComboBoxOption::High;
	}
	if (SelectedItem == FName(*NSLOCTEXT("FastMenuPlugin", "Epic", "Epic").ToString()))
	{
		AntiAliasing = EComboBoxOption::Epic;
	}
}

void UContentVideo::OnEffectChange(FName SelectedItem, ESelectInfo::Type SelectionType)
{
	if (SelectedItem == FName(*NSLOCTEXT("FastMenuPlugin", "Low", "Low").ToString()))
	{
		Effect = EComboBoxOption::Low;
	}
	if (SelectedItem == FName(*NSLOCTEXT("FastMenuPlugin", "Medium", "Medium").ToString()))
	{
		Effect = EComboBoxOption::Medium;
	}
	if (SelectedItem == FName(*NSLOCTEXT("FastMenuPlugin", "High", "High").ToString()))
	{
		Effect = EComboBoxOption::High;
	}
	if (SelectedItem == FName(*NSLOCTEXT("FastMenuPlugin", "Epic", "Epic").ToString()))
	{
		Effect = EComboBoxOption::Epic;
	}
}

void UContentVideo::OnDetailModeChange(FName SelectedItem, ESelectInfo::Type SelectionType)
{
	if (SelectedItem == FName(*NSLOCTEXT("FastMenuPlugin", "Low", "Low").ToString()))
	{
		DetailMode = EComboBoxOption::Low;
	}
	if (SelectedItem == FName(*NSLOCTEXT("FastMenuPlugin", "Medium", "Medium").ToString()))
	{
		DetailMode = EComboBoxOption::Medium;
	}
	if (SelectedItem == FName(*NSLOCTEXT("FastMenuPlugin", "High", "High").ToString()))
	{
		DetailMode = EComboBoxOption::High;
	}
	if (SelectedItem == FName(*NSLOCTEXT("FastMenuPlugin", "Epic", "Epic").ToString()))
	{
		DetailMode = EComboBoxOption::Epic;
	}
}

void UContentVideo::OnViewDistanceChange(FName SelectedItem, ESelectInfo::Type SelectionType)
{
	if (SelectedItem == FName(*NSLOCTEXT("FastMenuPlugin", "Short", "Short").ToString()))
	{
		ViewDistance = EComboBoxOption::Short;
	}
	if (SelectedItem == FName(*NSLOCTEXT("FastMenuPlugin", "Medium", "Medium").ToString()))
	{
		ViewDistance = EComboBoxOption::Medium;
	}
	if (SelectedItem == FName(*NSLOCTEXT("FastMenuPlugin", "Long", "Long").ToString()))
	{
		ViewDistance = EComboBoxOption::Long;
	}
}

void UContentVideo::SaveChanges()
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

	FVideoContentSettings CurrentVideoContentSettings = FVideoContentSettings{VideoResolution, Fullscreen, ShadowQuality, PostProcessing, TextureQuality, MaterialQuality, AntiAliasing, Effect, DetailMode, ViewDistance};
	if (CurrentSaveGame != nullptr)
	{
		CurrentSaveGame->SetSavedVideoSettings(CurrentVideoContentSettings);
		bool Success = UGameplayStatics::SaveGameToSlot(CurrentSaveGame, FString("FastMenuSaveGameSlot"), 0);
		if (!Success)
		{
			UE_LOG(LogTemp, Warning, TEXT("Save Game to Slot Failed"));
		}
	}
}

void UContentVideo::RestoreDefault()
{
	FVideoContentSettings DefaultVideoContentSettings;
	if (VideoResolution_FastMenuComboBoxKey)
	{
		VideoResolution_FastMenuComboBoxKey->SetSelectedOption(DefaultVideoContentSettings.VideoResolution);
	}
	if (Fullscreen_CheckBox)
	{
		if (DefaultVideoContentSettings.Fullscreen)
		{
			Fullscreen_CheckBox->SetCheckedState(ECheckBoxState::Checked);
		}
		else
		{
			Fullscreen_CheckBox->SetCheckedState(ECheckBoxState::Unchecked);
		}
	}
	if (ShadowQuality_FastMenuComboBoxKey)
	{
		switch (DefaultVideoContentSettings.ShadowQuality)
		{
		case EComboBoxOption::Low:
			ShadowQuality_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Low", "Low").ToString()));
			break;
		case EComboBoxOption::Medium:
			ShadowQuality_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Medium", "Medium").ToString()));
			break;
		case EComboBoxOption::High:
			ShadowQuality_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "High", "High").ToString()));
			break;
		case EComboBoxOption::Epic:
			ShadowQuality_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Epic", "Epic").ToString()));
			break;
		default:
			break;
		}
	}
	if (PostProcessing_FastMenuComboBoxKey)
	{
		switch (DefaultVideoContentSettings.PostProcessing)
		{
		case EComboBoxOption::Low:
			PostProcessing_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Low", "Low").ToString()));
			break;
		case EComboBoxOption::Medium:
			PostProcessing_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Medium", "Medium").ToString()));
			break;
		case EComboBoxOption::High:
			PostProcessing_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "High", "High").ToString()));
			break;
		case EComboBoxOption::Epic:
			PostProcessing_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Epic", "Epic").ToString()));
			break;
		default:
			break;
		}
	}
	if (TextureQuality_FastMenuComboBoxKey)
	{
		switch (DefaultVideoContentSettings.TextureQuality)
		{
		case EComboBoxOption::Low:
			TextureQuality_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Low", "Low").ToString()));
			break;
		case EComboBoxOption::Medium:
			TextureQuality_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Medium", "Medium").ToString()));
			break;
		case EComboBoxOption::High:
			TextureQuality_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "High", "High").ToString()));
			break;
		case EComboBoxOption::Epic:
			TextureQuality_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Epic", "Epic").ToString()));
			break;
		default:
			break;
		}
	}
	if (MaterialQuality_FastMenuComboBoxKey)
	{
		switch (DefaultVideoContentSettings.MaterialQuality)
		{
		case EComboBoxOption::Low:
			MaterialQuality_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Low", "Low").ToString()));
			break;
		case EComboBoxOption::Medium:
			MaterialQuality_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Medium", "Medium").ToString()));
			break;
		case EComboBoxOption::High:
			MaterialQuality_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "High", "High").ToString()));
			break;
		case EComboBoxOption::Epic:
			MaterialQuality_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Epic", "Epic").ToString()));
			break;
		default:
			break;
		}
	}
	if (AntiAliasing_FastMenuComboBoxKey)
	{
		switch (DefaultVideoContentSettings.AntiAliasing)
		{
		case EComboBoxOption::Low:
			AntiAliasing_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Low", "Low").ToString()));
			break;
		case EComboBoxOption::Medium:
			AntiAliasing_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Medium", "Medium").ToString()));
			break;
		case EComboBoxOption::High:
			AntiAliasing_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "High", "High").ToString()));
			break;
		case EComboBoxOption::Epic:
			AntiAliasing_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Epic", "Epic").ToString()));
			break;
		default:
			break;
		}
	}
	if (Effect_FastMenuComboBoxKey)
	{
		switch (DefaultVideoContentSettings.Effect)
		{
		case EComboBoxOption::Low:
			Effect_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Low", "Low").ToString()));
			break;
		case EComboBoxOption::Medium:
			Effect_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Medium", "Medium").ToString()));
			break;
		case EComboBoxOption::High:
			Effect_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "High", "High").ToString()));
			break;
		case EComboBoxOption::Epic:
			Effect_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Epic", "Epic").ToString()));
			break;
		default:
			break;
		}
	}
	if (DetailMode_FastMenuComboBoxKey)
	{
		switch (DefaultVideoContentSettings.DetailMode)
		{
		case EComboBoxOption::Low:
			DetailMode_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Low", "Low").ToString()));
			break;
		case EComboBoxOption::Medium:
			DetailMode_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Medium", "Medium").ToString()));
			break;
		case EComboBoxOption::High:
			DetailMode_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "High", "High").ToString()));
			break;
		case EComboBoxOption::Epic:
			DetailMode_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Epic", "Epic").ToString()));
			break;
		default:
			break;
		}
	}
	if (ViewDistance_FastMenuComboBoxKey)
	{
		switch (DefaultVideoContentSettings.ViewDistance)
		{
		case EComboBoxOption::Low:
			ViewDistance_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Short", "Short").ToString()));
			break;
		case EComboBoxOption::Medium:
			ViewDistance_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Medium", "Medium").ToString()));
			break;
		case EComboBoxOption::High:
			ViewDistance_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Long", "Long").ToString()));
			break;
		default:
			break;
		}
	}
}

void UContentVideo::SetupComboBoxes()
{
	if (ShadowQuality_FastMenuComboBoxKey)
	{
		ShadowQuality_FastMenuComboBoxKey->AddOption(FName(*NSLOCTEXT("FastMenuPlugin", "Low", "Low").ToString()));
		ShadowQuality_FastMenuComboBoxKey->AddOption(FName(*NSLOCTEXT("FastMenuPlugin", "Medium", "Medium").ToString()));
		ShadowQuality_FastMenuComboBoxKey->AddOption(FName(*NSLOCTEXT("FastMenuPlugin", "High", "High").ToString()));
		ShadowQuality_FastMenuComboBoxKey->AddOption(FName(*NSLOCTEXT("FastMenuPlugin", "Epic", "Epic").ToString()));
		ShadowQuality_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Epic", "Epic").ToString()));
	}
	if (PostProcessing_FastMenuComboBoxKey)
	{
		PostProcessing_FastMenuComboBoxKey->AddOption(FName(*NSLOCTEXT("FastMenuPlugin", "Low", "Low").ToString()));
		PostProcessing_FastMenuComboBoxKey->AddOption(FName(*NSLOCTEXT("FastMenuPlugin", "Medium", "Medium").ToString()));
		PostProcessing_FastMenuComboBoxKey->AddOption(FName(*NSLOCTEXT("FastMenuPlugin", "High", "High").ToString()));
		PostProcessing_FastMenuComboBoxKey->AddOption(FName(*NSLOCTEXT("FastMenuPlugin", "Epic", "Epic").ToString()));
		PostProcessing_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Epic", "Epic").ToString()));
	}
	if (TextureQuality_FastMenuComboBoxKey)
	{
		TextureQuality_FastMenuComboBoxKey->AddOption(FName(*NSLOCTEXT("FastMenuPlugin", "Low", "Low").ToString()));
		TextureQuality_FastMenuComboBoxKey->AddOption(FName(*NSLOCTEXT("FastMenuPlugin", "Medium", "Medium").ToString()));
		TextureQuality_FastMenuComboBoxKey->AddOption(FName(*NSLOCTEXT("FastMenuPlugin", "High", "High").ToString()));
		TextureQuality_FastMenuComboBoxKey->AddOption(FName(*NSLOCTEXT("FastMenuPlugin", "Epic", "Epic").ToString()));
		TextureQuality_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Epic", "Epic").ToString()));
	}
	if (MaterialQuality_FastMenuComboBoxKey)
	{
		MaterialQuality_FastMenuComboBoxKey->AddOption(FName(*NSLOCTEXT("FastMenuPlugin", "Low", "Low").ToString()));
		MaterialQuality_FastMenuComboBoxKey->AddOption(FName(*NSLOCTEXT("FastMenuPlugin", "Medium", "Medium").ToString()));
		MaterialQuality_FastMenuComboBoxKey->AddOption(FName(*NSLOCTEXT("FastMenuPlugin", "High", "High").ToString()));
		MaterialQuality_FastMenuComboBoxKey->AddOption(FName(*NSLOCTEXT("FastMenuPlugin", "Epic", "Epic").ToString()));
		MaterialQuality_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Epic", "Epic").ToString()));
	}
	if (AntiAliasing_FastMenuComboBoxKey)
	{
		AntiAliasing_FastMenuComboBoxKey->AddOption(FName(*NSLOCTEXT("FastMenuPlugin", "Low", "Low").ToString()));
		AntiAliasing_FastMenuComboBoxKey->AddOption(FName(*NSLOCTEXT("FastMenuPlugin", "Medium", "Medium").ToString()));
		AntiAliasing_FastMenuComboBoxKey->AddOption(FName(*NSLOCTEXT("FastMenuPlugin", "High", "High").ToString()));
		AntiAliasing_FastMenuComboBoxKey->AddOption(FName(*NSLOCTEXT("FastMenuPlugin", "Epic", "Epic").ToString()));
		AntiAliasing_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Epic", "Epic").ToString()));
	}
	if (Effect_FastMenuComboBoxKey)
	{
		Effect_FastMenuComboBoxKey->AddOption(FName(*NSLOCTEXT("FastMenuPlugin", "Low", "Low").ToString()));
		Effect_FastMenuComboBoxKey->AddOption(FName(*NSLOCTEXT("FastMenuPlugin", "Medium", "Medium").ToString()));
		Effect_FastMenuComboBoxKey->AddOption(FName(*NSLOCTEXT("FastMenuPlugin", "High", "High").ToString()));
		Effect_FastMenuComboBoxKey->AddOption(FName(*NSLOCTEXT("FastMenuPlugin", "Epic", "Epic").ToString()));
		Effect_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Epic", "Epic").ToString()));
	}
	if (DetailMode_FastMenuComboBoxKey)
	{
		DetailMode_FastMenuComboBoxKey->AddOption(FName(*NSLOCTEXT("FastMenuPlugin", "Low", "Low").ToString()));
		DetailMode_FastMenuComboBoxKey->AddOption(FName(*NSLOCTEXT("FastMenuPlugin", "Medium", "Medium").ToString()));
		DetailMode_FastMenuComboBoxKey->AddOption(FName(*NSLOCTEXT("FastMenuPlugin", "High", "High").ToString()));
		DetailMode_FastMenuComboBoxKey->AddOption(FName(*NSLOCTEXT("FastMenuPlugin", "Epic", "Epic").ToString()));
		DetailMode_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Epic", "Epic").ToString()));
	}
	if (ViewDistance_FastMenuComboBoxKey)
	{
		ViewDistance_FastMenuComboBoxKey->AddOption(FName(*NSLOCTEXT("FastMenuPlugin", "Short", "Short").ToString()));
		ViewDistance_FastMenuComboBoxKey->AddOption(FName(*NSLOCTEXT("FastMenuPlugin", "Medium", "Medium").ToString()));
		ViewDistance_FastMenuComboBoxKey->AddOption(FName(*NSLOCTEXT("FastMenuPlugin", "Long", "Long").ToString()));
		ViewDistance_FastMenuComboBoxKey->SetSelectedOption(FName(*NSLOCTEXT("FastMenuPlugin", "Long", "Long").ToString()));
	}
}

void UContentVideo::ApplyChanges()
{
	// Run command for each setting, then save settings to savegame object
	APlayerController* OwningPlayer = GetOwningPlayer();
	if (OwningPlayer)
	{
		// Resolution
		FString Command = FString::Printf(TEXT("r.setRes %s"), *(VideoResolution.ToString()));
		OwningPlayer->ConsoleCommand(*Command);
		//Fullscreen
		if (Fullscreen)
		{
			UE_LOG(LogTemp, Warning, TEXT("Set Fullscreen"));
			UGameUserSettings* GameUserSettings = UGameUserSettings::GetGameUserSettings();
			if (GameUserSettings != nullptr)
			{
				GameUserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Set Windowed"));
			UGameUserSettings* GameUserSettings = UGameUserSettings::GetGameUserSettings();
			if (GameUserSettings != nullptr)
			{
				GameUserSettings->SetFullscreenMode(EWindowMode::Windowed);
			}
		}
		//Shadow
		switch (ShadowQuality)
		{
		case EComboBoxOption::Low:
			OwningPlayer->ConsoleCommand("sg.ShadowQuality 0");
			break;
		case EComboBoxOption::Medium:
			OwningPlayer->ConsoleCommand("sg.ShadowQuality 1");
			break;
		case EComboBoxOption::High:
			OwningPlayer->ConsoleCommand("sg.ShadowQuality 2");
			break;
		case EComboBoxOption::Epic:
			OwningPlayer->ConsoleCommand("sg.ShadowQuality 3");
			break;
		default:
			break;
		}

		//Post Processing
		switch (PostProcessing)
		{
		case EComboBoxOption::Low:
			OwningPlayer->ConsoleCommand("sg.PostProcessQuality 0");
			break;
		case EComboBoxOption::Medium:
			OwningPlayer->ConsoleCommand("sg.PostProcessQuality 1");
			break;
		case EComboBoxOption::High:
			OwningPlayer->ConsoleCommand("sg.PostProcessQuality 2");
			break;
		case EComboBoxOption::Epic:
			OwningPlayer->ConsoleCommand("sg.PostProcessQuality 3");
			break;
		default:
			break;
		}
		//Texture
		switch (TextureQuality)
		{
		case EComboBoxOption::Low:
			OwningPlayer->ConsoleCommand("sg.TextureQuality 0");
			break;
		case EComboBoxOption::Medium:
			OwningPlayer->ConsoleCommand("sg.TextureQuality 1");
			break;
		case EComboBoxOption::High:
			OwningPlayer->ConsoleCommand("sg.TextureQuality 2");
			break;
		case EComboBoxOption::Epic:
			OwningPlayer->ConsoleCommand("sg.TextureQuality 3");
			break;
		default:
			break;
		}
		//Material
		switch (MaterialQuality)
		{
		case EComboBoxOption::Low:
			OwningPlayer->ConsoleCommand("r.MaterialQualityLevel 0");
			break;
		case EComboBoxOption::Medium:
			OwningPlayer->ConsoleCommand("r.MaterialQualityLevel 1");
			break;
		case EComboBoxOption::High:
			OwningPlayer->ConsoleCommand("r.MaterialQualityLevel 2");
			break;
		case EComboBoxOption::Epic:
			OwningPlayer->ConsoleCommand("r.MaterialQualityLevel 3");
			break;
		default:
			break;
		}
		//Anti-Aliasing
		switch (AntiAliasing)
		{
		case EComboBoxOption::Low:
			OwningPlayer->ConsoleCommand("r.PostProcessAAQuality 0");
			break;
		case EComboBoxOption::Medium:
			OwningPlayer->ConsoleCommand("r.PostProcessAAQuality 1");
			break;
		case EComboBoxOption::High:
			OwningPlayer->ConsoleCommand("r.PostProcessAAQuality 2");
			break;
		case EComboBoxOption::Epic:
			OwningPlayer->ConsoleCommand("r.PostProcessAAQuality 3");
			break;
		default:
			break;
		}
		//Effect
		switch (Effect)
		{
		case EComboBoxOption::Low:
			OwningPlayer->ConsoleCommand("sg.EffectsQuality 0");
			break;
		case EComboBoxOption::Medium:
			OwningPlayer->ConsoleCommand("sg.EffectsQuality 1");
			break;
		case EComboBoxOption::High:
			OwningPlayer->ConsoleCommand("sg.EffectsQuality 2");
			break;
		case EComboBoxOption::Epic:
			OwningPlayer->ConsoleCommand("sg.EffectsQuality 3");
			break;
		default:
			break;
		}
		//DetailMode
		switch (DetailMode)
		{
		case EComboBoxOption::Low:
			OwningPlayer->ConsoleCommand("r.DetailMode 0");
			break;
		case EComboBoxOption::Medium:
			OwningPlayer->ConsoleCommand("r.DetailMode 1");
			break;
		case EComboBoxOption::High:
			OwningPlayer->ConsoleCommand("r.DetailMode 2");
			break;
		case EComboBoxOption::Epic:
			OwningPlayer->ConsoleCommand("r.DetailMode 3");
			break;
		default:
			break;
		}
		//View Distance
		switch (ViewDistance)
		{
		case EComboBoxOption::Short:
			OwningPlayer->ConsoleCommand("r.ViewDistanceScale 0.4");
			break;
		case EComboBoxOption::Medium:
			OwningPlayer->ConsoleCommand("r.ViewDistanceScale 0.7");
			break;
		case EComboBoxOption::Long:
			OwningPlayer->ConsoleCommand("r.ViewDistanceScale 1.0");
			break;
		default:
			break;
		}
	}
	//Save Settings to File
	SaveChanges();
}
