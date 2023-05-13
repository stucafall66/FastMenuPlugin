// Fill out your copyright notice in the Description page of Project Settings.


#include "FastMenuSaveGame.h"
#include "Kismet/GameplayStatics.h"


void UFastMenuSaveGame::SetSavedVideoSettings(const FVideoContentSettings& Settings)
{
	SavedVideoContentSettings = Settings;
}

void UFastMenuSaveGame::SetSavedAudioSettings(const FAudioContentSettings& Settings)
{
	SavedAudioContentSettings = Settings;
}

void UFastMenuSaveGame::SetSavedControlSettings(const FControlContentSettings& Settings)
{
	SavedControlContentSettings = Settings;
}

void UFastMenuSaveGame::SetSavedMiscellaneousSettings(const FMiscellaneousContentSettings& Settings)
{
	SavedMiscellaneousContentSettings = Settings;
}
