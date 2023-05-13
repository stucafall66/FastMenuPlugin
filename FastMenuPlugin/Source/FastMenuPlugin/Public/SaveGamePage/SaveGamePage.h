// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SaveGamePage.generated.h"

/**
 * 
 */
UCLASS()
class FASTMENUPLUGIN_API USaveGamePage : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "FastMenuPlugin")
	void ClearSaveGameItems();

	UFUNCTION(BlueprintImplementableEvent, Category = "FastMenuPlugin")
	class USaveGameItem* GenerateSaveGameItem(const FText& SavedGameName, const FText& CreatedTimestamp, const FText& UpdatedTimestamp);

	UFUNCTION(BlueprintImplementableEvent, Category = "FastMenuPlugin")
	class UConfirmOverwrite* PopupConfirmOverwriteWindow(const FText& OverwriteName);

	UFUNCTION(BlueprintImplementableEvent, Category = "FastMenuPlugin")
	class UDeleteSaveGame* PopupConfirmDeleteWindow(const FText& DeleteName);

	UFUNCTION(BlueprintImplementableEvent, Category = "FastMenuPlugin")
	void ResetSaveGameInfo();

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "FastMenuPlugin")
	class UImage* ScreenShot;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "FastMenuPlugin")
	class UTextBlock* CreatedTimeText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "FastMenuPlugin")
	UTextBlock* UpdatedTimeText;

protected:
	virtual void NativeOnInitialized();

private:
	UFUNCTION(BlueprintCallable, Category = "FastMenuPlugin")
	void SaveCurrentGame();

	UFUNCTION()
	void HandleSaveGameItemClicked(USaveGameItem* ClickedSaveGameItem);

	UFUNCTION()
	void HandleDeleteSaveGameClicked(USaveGameItem* ClickedSaveGameItem);

	UFUNCTION()
	void ReloadSaveGameItems();

	UFUNCTION()
	void OnSaveGameEditableTextChange(const FText& Text);

	UFUNCTION()
	void SaveScreenShot(FString SaveGameName);

	UFUNCTION()
	void DeleteScreenShot(FString SaveGameName);

	void SetSaveGameInfo(USaveGameItem* SaveGameItem);

private:
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "FastMenuPlugin")
	class UEditableTextBox* EnterSaveGameEditableText;

	UPROPERTY()
	USaveGameItem* ActiveSavedGameItem{nullptr};

	/*UPROPERTY()
	TArray<USaveGameItem*> SaveGameItems;*/
};
