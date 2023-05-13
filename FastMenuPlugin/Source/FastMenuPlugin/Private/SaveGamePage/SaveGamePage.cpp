// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGamePage/SaveGamePage.h"
//#include "Components/ScrollBox.h"
#include "Components/EditableTextBox.h"
#include "SaveGamePage/SaveGameItem.h"
#include "Misc/DateTime.h"
#include "SaveGameStructure.h"
#include "Kismet/GameplayStatics.h"
#include "HAL/FileManager.h"
#include "Components/Button.h"
#include "SaveGamePage/ConfirmOverwrite.h"
#include "SaveGamePage/DeleteSaveGame.h"
#include "Misc/Paths.h"
#include "Components/Image.h"
#include "ImageUtils.h"
#include "Components/TextBlock.h"


void USaveGamePage::NativeOnInitialized()
{
	ReloadSaveGameItems();
	EnterSaveGameEditableText->OnTextChanged.AddDynamic(this, &ThisClass::OnSaveGameEditableTextChange);
}

void USaveGamePage::SaveCurrentGame()
{
	if (ActiveSavedGameItem != nullptr)
	{
		// You select a SavedGameItem by mouse, overwrite this save game
		FString SaveGameName = ActiveSavedGameItem->GetSavedGameName().ToString();
		UE_LOG(LogTemp, Warning, TEXT("SaveGameName is %s"), *SaveGameName);
		if (!SaveGameName.IsEmpty())
		{
			if (UGameplayStatics::DoesSaveGameExist(SaveGameName, 0))
			{
				UE_LOG(LogTemp, Warning, TEXT("Save file exists"));
				// Do you want to overwrite this save file
				UConfirmOverwrite* ConfirmOverwriteWindow = PopupConfirmOverwriteWindow(FText::FromString(SaveGameName));
				ConfirmOverwriteWindow->OnConfirmOverwriteClicked.AddUObject(this, &USaveGamePage::SaveScreenShot, SaveGameName);
				ConfirmOverwriteWindow->OnConfirmOverwriteClicked.AddUObject(this, &USaveGamePage::ReloadSaveGameItems);
			}
		}
	}
	else
	{
		// Save game based on entered save game name text
		FString SaveGameName = EnterSaveGameEditableText->GetText().ToString().Replace(TEXT(" "), TEXT(""));
		UE_LOG(LogTemp, Warning, TEXT("SaveGameName is %s"), *SaveGameName);
		if (!SaveGameName.IsEmpty())
		{
			USaveGameStructure* CurrentSaveGame = nullptr;
			if (UGameplayStatics::DoesSaveGameExist(SaveGameName, 0))
			{
				UE_LOG(LogTemp, Warning, TEXT("Save file exists"));
				// Do you want to overwrite this save file
				UConfirmOverwrite* ConfirmOverwriteWindow = PopupConfirmOverwriteWindow(FText::FromString(SaveGameName));
				ConfirmOverwriteWindow->OnConfirmOverwriteClicked.AddUObject(this, &USaveGamePage::SaveScreenShot, SaveGameName);
				ConfirmOverwriteWindow->OnConfirmOverwriteClicked.AddUObject(this, &USaveGamePage::ReloadSaveGameItems);
				// ConfirmOverwriteWindow->OnConfirmOverwriteClicked.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(USaveGamePage, ReloadSaveGameItems));
			}
			else
			{
				// Create a new save file based on this name
				// You need to implement your own game save logic here
				UE_LOG(LogTemp, Warning, TEXT("Save file does not exist"));
				UE_LOG(LogTemp, Warning, TEXT("You need to implement your own game save logic here"));

				CurrentSaveGame = Cast<USaveGameStructure>(UGameplayStatics::CreateSaveGameObject(USaveGameStructure::StaticClass()));
				FDateTime CurrentDateTime = FDateTime::Now();
				CurrentSaveGame->SetCreatedTimeText(FText::FromString(CurrentDateTime.ToString()));
				CurrentSaveGame->SetUpdatedTimeText(FText::FromString(CurrentDateTime.ToString()));
				bool Success = UGameplayStatics::SaveGameToSlot(CurrentSaveGame, SaveGameName, 0);
				if (!Success)
				{
					UE_LOG(LogTemp, Warning, TEXT("Save Game to Slot Failed"));
				}
				else
				{
					// Add a new SaveGameItem to the scrollbox
					USaveGameItem* GeneratedSaveGameItem = GenerateSaveGameItem(FText::FromString(SaveGameName), FText::FromString(CurrentDateTime.ToString()), FText::FromString(CurrentDateTime.ToString()));
					GeneratedSaveGameItem->OnSaveGameItemClicked.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(USaveGamePage, HandleSaveGameItemClicked));
					GeneratedSaveGameItem->OnDeleteSaveGameClicked.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(USaveGamePage, HandleDeleteSaveGameClicked));
					// Take Screenshot
					SaveScreenShot(SaveGameName);
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Save Game Name is empty!"));
		}
	}
}

void USaveGamePage::HandleSaveGameItemClicked(USaveGameItem* ClickedSaveGameItem)
{
	// Set previous active widget to inactive
	// Set this widget to active
	UE_LOG(LogTemp, Warning, TEXT("In HandleSaveGameItemClicked"));
	if (ActiveSavedGameItem != nullptr)
	{
		ActiveSavedGameItem->SetInactive();
	}
	if (ClickedSaveGameItem != nullptr)
	{
		// Clear SaveGameEditableText
		EnterSaveGameEditableText->SetText(FText());
		ClickedSaveGameItem->SetActive();
		ActiveSavedGameItem = ClickedSaveGameItem;
		// Set SaveGameInfo
		SetSaveGameInfo(ClickedSaveGameItem);
	}
}

void USaveGamePage::HandleDeleteSaveGameClicked(USaveGameItem* ClickedSaveGameItem)
{
	UE_LOG(LogTemp, Warning, TEXT("Delete Save Game Btn clicked"));
	// Do you want to delete this save file
	if (ClickedSaveGameItem != nullptr)
	{
		UDeleteSaveGame* ConfirmDeleteWindow = PopupConfirmDeleteWindow(ClickedSaveGameItem->GetSavedGameName());
		ConfirmDeleteWindow->OnConfirmDeleteClicked.AddUObject(this, &USaveGamePage::ReloadSaveGameItems);
		ConfirmDeleteWindow->OnConfirmDeleteClicked.AddUObject(this, &USaveGamePage::DeleteScreenShot, ClickedSaveGameItem->GetSavedGameName().ToString());
	}
}

void USaveGamePage::ReloadSaveGameItems()
{
	// Load all saved files, generate SaveGameItem for each one
	ActiveSavedGameItem = nullptr;
	TArray<FString> FileNames;
	IFileManager &FileMgr = IFileManager::Get();
	// FileMgr.SetSandboxEnabled(true);
	FString wildcard("*.sav"); // May be "" (empty string) to search all files
	/*UE_LOG(LogTemp, Warning, TEXT("Game Saved Dir is %s"), *FPaths::ProjectUserDir());
	if (FPaths::ShouldSaveToUserDir())
	{
		UE_LOG(LogTemp, Warning, TEXT("Should Save to User Dir"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Should Not Save to User Dir"));
	}*/
	// EnterSaveGameEditableText->SetText(FText::FromString(FPaths::ProjectSavedDir()));
	FString search_path(FPaths::Combine(*FPaths::ProjectSavedDir(), TEXT("SaveGames"), *wildcard));

	FileMgr.FindFiles(FileNames, *search_path,
		true,  // to list files
		false); // to skip directories

	ClearSaveGameItems();
	// SaveGameItems.Empty();
	for (FString filename : FileNames)
	{
		if (filename != FString("FastMenuSaveGameSlot.sav"))
		{
			FString tempFilename(filename);
			tempFilename.RemoveFromEnd(".sav");

			USaveGameStructure* ThisSaveGame = Cast<USaveGameStructure>(UGameplayStatics::LoadGameFromSlot(tempFilename, 0));
			if (ThisSaveGame != nullptr)
			{
				USaveGameItem* GeneratedSaveGameItem = nullptr;
				if (!ThisSaveGame->GetUpdatedTimeText().IsEmpty())
				{
					GeneratedSaveGameItem = GenerateSaveGameItem(FText::FromString(tempFilename), ThisSaveGame->GetCreatedTimeText(), ThisSaveGame->GetUpdatedTimeText());
				}
				else
				{
					GeneratedSaveGameItem = GenerateSaveGameItem(FText::FromString(tempFilename), ThisSaveGame->GetCreatedTimeText(), FText::FromString(FString("--")));
				}
				GeneratedSaveGameItem->OnSaveGameItemClicked.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(USaveGamePage, HandleSaveGameItemClicked));
				GeneratedSaveGameItem->OnDeleteSaveGameClicked.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(USaveGamePage, HandleDeleteSaveGameClicked));
				// SaveGameItems.Add(GeneratedSaveGameItem);
			}
		}
	}

	FileNames.Empty();// Clear array
	ResetSaveGameInfo();
}

void USaveGamePage::OnSaveGameEditableTextChange(const FText& Text)
{
	// Inactive all SaveGameItem selections
	if (ActiveSavedGameItem != nullptr)
	{
		ActiveSavedGameItem->SetInactive();
		ActiveSavedGameItem = nullptr;
	}
}

void USaveGamePage::SaveScreenShot(FString SaveGameName)
{
	UE_LOG(LogTemp, Warning, TEXT("Save Screen Shot: %s"), *SaveGameName);

	APlayerController* OwningPlayer = GetOwningPlayer();
	if (OwningPlayer)
	{
		// Resolution
		FString Command = FString::Printf(TEXT("HighResShot 1 filename=%s.png"), *SaveGameName);
		OwningPlayer->ConsoleCommand(*Command);
	}
}

void USaveGamePage::DeleteScreenShot(FString SaveGameName)
{
	UE_LOG(LogTemp, Warning, TEXT("Delete Screen Shot: %s"), *SaveGameName);

	FString DeleteFilePath;
	if (GetWorld()->IsEditorWorld())
	{
		DeleteFilePath = FString(FPaths::Combine(*FPaths::ProjectSavedDir(), TEXT("Screenshots/WindowsEditor"), SaveGameName + FString(".png")));
	}
	else
	{
		DeleteFilePath = FString(FPaths::Combine(*FPaths::ProjectSavedDir(), TEXT("Screenshots/Windows"), SaveGameName + FString(".png")));
	}

	if (!DeleteFilePath.IsEmpty())
	{
		if (FPaths::ValidatePath(DeleteFilePath) && FPaths::FileExists(DeleteFilePath))
		{
			IFileManager& FileManager = IFileManager::Get(); 
			FileManager.Delete(*DeleteFilePath);
		}
	}
}

void USaveGamePage::SetSaveGameInfo(USaveGameItem* SaveGameItem)
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
