// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SettingStructures.h"
#include "FastMenuSaveGame.generated.h"

/**
 * 
 */


UCLASS()
class UFastMenuSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	void SetSavedVideoSettings(const FVideoContentSettings& Settings);
	void SetSavedAudioSettings(const FAudioContentSettings& Settings);
	void SetSavedControlSettings(const FControlContentSettings& Settings);
	void SetSavedMiscellaneousSettings(const FMiscellaneousContentSettings& Settings);

	FORCEINLINE FVideoContentSettings GetSavedVideoSettings() { return SavedVideoContentSettings; }
	FORCEINLINE FAudioContentSettings GetSavedAudioSettings() { return SavedAudioContentSettings; }
	FORCEINLINE FControlContentSettings GetSavedControlSettings() { return SavedControlContentSettings; }
	FORCEINLINE FMiscellaneousContentSettings GetSavedMiscellaneousSettings() { return SavedMiscellaneousContentSettings; }

private:
	UPROPERTY()
	FVideoContentSettings SavedVideoContentSettings;

	UPROPERTY()
	FAudioContentSettings SavedAudioContentSettings;

	UPROPERTY()
	FControlContentSettings SavedControlContentSettings;

	UPROPERTY()
	FMiscellaneousContentSettings SavedMiscellaneousContentSettings;
};
