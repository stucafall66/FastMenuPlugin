// Fill out your copyright notice in the Description page of Project Settings.


#include "ContentPage/ContentAudio.h"
#include "Kismet/GameplayStatics.h"
#include "FastMenuSaveGame.h"
#include "SettingStructures.h"
#include "ContentPage/FastMenuSlider.h"
#include "Components/Slider.h"

void UContentAudio::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// Load Saved Game
	UFastMenuSaveGame* CurrentSaveGame = Cast<UFastMenuSaveGame>(UGameplayStatics::LoadGameFromSlot(FString("FastMenuSaveGameSlot"), 0));
	if (CurrentSaveGame != nullptr)
	{
		FAudioContentSettings CurrentAudioContentSetting = CurrentSaveGame->GetSavedAudioSettings();
		if (MasterVolumeSlider != nullptr && MasterVolumeSlider->Slider != nullptr)
		{
			MasterVolumeSlider->Slider->SetValue(CurrentAudioContentSetting.MasterVolume);
			MasterVolume = CurrentAudioContentSetting.MasterVolume;
		}
		if (SoundEffectVolumeSlider != nullptr && SoundEffectVolumeSlider->Slider != nullptr)
		{
			SoundEffectVolumeSlider->Slider->SetValue(CurrentAudioContentSetting.SoundEffectVolume);
			SoundEffectVolume = CurrentAudioContentSetting.SoundEffectVolume;
		}
		if (AmbientVolumeSlider != nullptr && AmbientVolumeSlider->Slider != nullptr)
		{
			AmbientVolumeSlider->Slider->SetValue(CurrentAudioContentSetting.AmbientVolume);
			AmbientVolume = CurrentAudioContentSetting.AmbientVolume;
		}
		if (MusicVolumeSlider != nullptr && MusicVolumeSlider->Slider != nullptr)
		{
			MusicVolumeSlider->Slider->SetValue(CurrentAudioContentSetting.MusicVolume);
			MusicVolume = CurrentAudioContentSetting.MusicVolume;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CurrentSaveGame is nullptr"));
	}
}

void UContentAudio::HandleMasterVolumeChange(float Value)
{
	MasterVolume = Value;
}

void UContentAudio::HandleSoundEffectVolumeChange(float Value)
{
	SoundEffectVolume = Value;
}

void UContentAudio::HandleAmbientVolumeChange(float Value)
{
	AmbientVolume = Value;
}

void UContentAudio::HandleMusicVolumeChange(float Value)
{
	MusicVolume = Value;
}

void UContentAudio::SaveChanges()
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

	FAudioContentSettings CurrentAudioContentSettings = FAudioContentSettings{ MasterVolume, SoundEffectVolume, AmbientVolume, MusicVolume };
	if (CurrentSaveGame != nullptr)
	{
		CurrentSaveGame->SetSavedAudioSettings(CurrentAudioContentSettings);
		UE_LOG(LogTemp, Warning, TEXT("BBB %f"), CurrentSaveGame->GetSavedAudioSettings().SoundEffectVolume );
		bool Success = UGameplayStatics::SaveGameToSlot(CurrentSaveGame, FString("FastMenuSaveGameSlot"), 0);
		if (!Success)
		{
			UE_LOG(LogTemp, Warning, TEXT("Save Game to Slot Failed"));
		}
	}
}

void UContentAudio::RestoreDefault()
{
	FAudioContentSettings DefaultAudioContentSettings;
	if (MasterVolumeSlider)
	{
		MasterVolumeSlider->Slider->SetValue(DefaultAudioContentSettings.MasterVolume);
	}
	if (SoundEffectVolumeSlider)
	{
		SoundEffectVolumeSlider->Slider->SetValue(DefaultAudioContentSettings.SoundEffectVolume);
	}
	if (AmbientVolumeSlider)
	{
		AmbientVolumeSlider->Slider->SetValue(DefaultAudioContentSettings.AmbientVolume);
	}
	if (MusicVolumeSlider)
	{
		MusicVolumeSlider->Slider->SetValue(DefaultAudioContentSettings.MusicVolume);
	}
	MasterVolume = 1.f;
	SoundEffectVolume = 1.f;
	AmbientVolume = 1.f;
	MusicVolume = 1.f;
}

void UContentAudio::ApplyChanges()
{
	Super::ApplyChanges();
	HandleVolumes();
	SaveChanges();
}