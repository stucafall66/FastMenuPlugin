// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DeleteSaveGame.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FOnConfirmDeleteClicked);

UCLASS()
class FASTMENUPLUGIN_API UDeleteSaveGame : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "FastMenuPlugin")
		void SetSaveGameName(const FText& SaveGameNameText);

public:
	FOnConfirmDeleteClicked OnConfirmDeleteClicked;

private:
	UFUNCTION(BlueprintCallable, Category = "FastMenuPlugin")
		void HandleConfirmClicked();

private:
	UPROPERTY()
		FText SaveGameName {
		FText()
	};

	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "FastMenuPlugin")
	class UTextBlock* DeleteText;
};
