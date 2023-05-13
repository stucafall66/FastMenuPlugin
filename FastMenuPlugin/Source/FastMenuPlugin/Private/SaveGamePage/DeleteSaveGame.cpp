// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGamePage/DeleteSaveGame.h"
#include "Components/TextBlock.h"
#include "SaveGameStructure.h"
#include "Kismet/GameplayStatics.h"

void UDeleteSaveGame::SetSaveGameName(const FText& SaveGameNameText)
{
	SaveGameName = SaveGameNameText;
	// Set information text
	DeleteText->SetText(FText::Format(NSLOCTEXT("FastMenuPlugin", "DeleteText", "This will delete \"{0}\", please confirm"), SaveGameName));
}

void UDeleteSaveGame::HandleConfirmClicked()
{
	if (!SaveGameName.IsEmpty())
	{
		if (UGameplayStatics::DoesSaveGameExist(SaveGameName.ToString(), 0))
		{
			bool Success = UGameplayStatics::DeleteGameInSlot(SaveGameName.ToString(), 0);
			if (!Success)
			{
				UE_LOG(LogTemp, Warning, TEXT("Delete Save Game Failed"));
			}
		}
	}
	if (!IsDesignTime())
	{
		OnConfirmDeleteClicked.Broadcast();
	}

	RemoveFromParent();
}
