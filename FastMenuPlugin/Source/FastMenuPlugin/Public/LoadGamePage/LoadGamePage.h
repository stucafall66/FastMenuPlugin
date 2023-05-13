// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadGamePage.generated.h"

/**
 * 
 */
UCLASS()
class FASTMENUPLUGIN_API ULoadGamePage : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "FastMenuPlugin")
	void ClearLoadGameItems();

	UFUNCTION(BlueprintImplementableEvent, Category = "FastMenuPlugin")
	class ULoadGameItem* GenerateLoadGameItem(const FText& SavedGameName, const FText& CreatedTimestamp, const FText& UpdatedTimestamp);

	UFUNCTION(BlueprintImplementableEvent, Category = "FastMenuPlugin")
	void ResetLoadGameInfo();

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
	void LoadCurrentGame();

	UFUNCTION()
	void HandleLoadGameItemClicked(ULoadGameItem* ClickedSaveGameItem);

	UFUNCTION()
	void ReloadLoadGameItems();

	void SetLoadGameInfo(ULoadGameItem* SaveGameItem);

private:
	UPROPERTY()
	ULoadGameItem* ActiveLoadedGameItem { nullptr };

};
