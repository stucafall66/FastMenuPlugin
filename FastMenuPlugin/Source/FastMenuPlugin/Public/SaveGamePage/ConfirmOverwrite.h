// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ConfirmOverwrite.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FOnConfirmOverwriteClicked);

UCLASS()
class FASTMENUPLUGIN_API UConfirmOverwrite : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "FastMenuPlugin")
	void SetSaveGameName(const FText& SaveGameNameText);

public:
	// UPROPERTY()
	FOnConfirmOverwriteClicked OnConfirmOverwriteClicked;

private:
	UFUNCTION(BlueprintCallable, Category = "FastMenuPlugin")
	void HandleConfirmClicked();

private:
	UPROPERTY()
	FText SaveGameName { FText() };

	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "FastMenuPlugin")
	class UTextBlock* OverwriteText;
};
