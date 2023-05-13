// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGamePage/ConfirmOverwrite.h"
#include "Components/TextBlock.h"
#include "SaveGameStructure.h"
#include "Kismet/GameplayStatics.h"

void UConfirmOverwrite::SetSaveGameName(const FText& SaveGameNameText)
{
	SaveGameName = SaveGameNameText;
	// Set information text
	OverwriteText->SetText(FText::Format(NSLOCTEXT("FastMenuPlugin", "OverwriteText", "This will overwrite \"{0}\", please confirm"), SaveGameName));
}

void UConfirmOverwrite::HandleConfirmClicked()
{
	// Load the SaveGame file, then Save it 
	if (!SaveGameName.IsEmpty())
	{
		if (UGameplayStatics::DoesSaveGameExist(SaveGameName.ToString(), 0))
		{
			USaveGameStructure* CurrentSaveGame = Cast<USaveGameStructure>(UGameplayStatics::LoadGameFromSlot(SaveGameName.ToString(), 0));
			if (CurrentSaveGame != nullptr)
			{
				// TODO: Add your own overwrite logic here
				// Set Update Time
				FDateTime CurrentDateTime = FDateTime::Now();
				CurrentSaveGame->SetUpdatedTimeText(FText::FromString(CurrentDateTime.ToString()));
				bool Success = UGameplayStatics::SaveGameToSlot(CurrentSaveGame, SaveGameName.ToString(), 0);
				if (!Success)
				{
					UE_LOG(LogTemp, Warning, TEXT("Save Game to Slot Failed"));
				}
			}
		}
	}
	if (!IsDesignTime())
	{
		OnConfirmOverwriteClicked.Broadcast();
	}

	RemoveFromParent();
}
