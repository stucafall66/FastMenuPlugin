// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadGamePage/LoadGamePage.h"
#include "LoadGamePage/LoadGameItem.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "SaveGameStructure.h"
#include "Kismet/GameplayStatics.h"
#include "ImageUtils.h"
#include "HAL/FileManager.h"

void ULoadGamePage::NativeOnInitialized()
{
	ReloadLoadGameItems();
}

void ULoadGamePage::LoadCurrentGame()
{
	UE_LOG(LogTemp, Warning, TEXT("You need to implement load game logic here"));
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void ULoadGamePage::HandleLoadGameItemClicked(ULoadGameItem* ClickedSaveGameItem)
{
	// Set previous active widget to inactive
	// Set this widget to active
	UE_LOG(LogTemp, Warning, TEXT("In HandleLoadGameItemClicked"));
	if (ActiveLoadedGameItem != nullptr)
	{
		ActiveLoadedGameItem->SetInactive();
	}
	if (ClickedSaveGameItem != nullptr)
	{
		ClickedSaveGameItem->SetActive();
		ActiveLoadedGameItem = ClickedSaveGameItem;
		// Set SaveGameInfo
		SetLoadGameInfo(ClickedSaveGameItem);
	}
}

void ULoadGamePage::ReloadLoadGameItems()
{
	// Load all saved files, generate SaveGameItem for each one
	ActiveLoadedGameItem = nullptr;
	TArray<FString> FileNames;
	IFileManager& FileMgr = IFileManager::Get();
	FString wildcard("*.sav"); // May be "" (empty string) to search all files
	FString search_path(FPaths::Combine(*FPaths::ProjectSavedDir(), TEXT("SaveGames"), *wildcard));

	FileMgr.FindFiles(FileNames, *search_path,
		true,  // to list files
		false); // to skip directories

	ClearLoadGameItems();
	for (FString filename : FileNames)
	{
		if (filename != FString("FastMenuSaveGameSlot.sav"))
		{
			FString tempFilename(filename);
			tempFilename.RemoveFromEnd(".sav");

			USaveGameStructure* ThisSaveGame = Cast<USaveGameStructure>(UGameplayStatics::LoadGameFromSlot(tempFilename, 0));
			if (ThisSaveGame != nullptr)
			{
				ULoadGameItem* GeneratedLoadGameItem = nullptr;
				if (!ThisSaveGame->GetUpdatedTimeText().IsEmpty())
				{
					GeneratedLoadGameItem = GenerateLoadGameItem(FText::FromString(tempFilename), ThisSaveGame->GetCreatedTimeText(), ThisSaveGame->GetUpdatedTimeText());
				}
				else
				{
					GeneratedLoadGameItem = GenerateLoadGameItem(FText::FromString(tempFilename), ThisSaveGame->GetCreatedTimeText(), FText::FromString(FString("--")));
				}
				GeneratedLoadGameItem->OnLoadGameItemClicked.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(ULoadGamePage, HandleLoadGameItemClicked));
			}
		}
	}

	FileNames.Empty();// Clear array
	ResetLoadGameInfo();
}

void ULoadGamePage::SetLoadGameInfo(ULoadGameItem* SaveGameItem)
{
	if (SaveGameItem != nullptr)
	{
		FString SaveGameName = SaveGameItem->GetSavedGameName().ToString();
		// Set ScreenShot
		if (ScreenShot != nullptr)
		{
			FString ScreenShotFilePath;
			if (GetWorld()->IsEditorWorld())
			{
				ScreenShotFilePath = FString(FPaths::Combine(*FPaths::ProjectSavedDir(), TEXT("Screenshots/WindowsEditor"), SaveGameName + FString(".png")));
			}
			else
			{
				ScreenShotFilePath = FString(FPaths::Combine(*FPaths::ProjectSavedDir(), TEXT("Screenshots/Windows"), SaveGameName + FString(".png")));
			}

			UTexture2D* ScreenShotTexture = FImageUtils::ImportFileAsTexture2D(ScreenShotFilePath);
			if (ScreenShotTexture != nullptr)
			{
				ScreenShot->SetBrushFromTexture(ScreenShotTexture, true);
			}
		}
		// Set CreatedTime & UpdatedTime
		if (CreatedTimeText != nullptr && UpdatedTimeText != nullptr)
		{
			CreatedTimeText->SetText(SaveGameItem->CreatedTimestampText);
			UpdatedTimeText->SetText(SaveGameItem->UpdatedTimestampText);
		}
	}
}
