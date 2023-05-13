// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadGameItem.generated.h"

/**
 * 
 */
UCLASS()
class FASTMENUPLUGIN_API ULoadGameItem : public UUserWidget
{
	GENERATED_BODY()
public:
	DECLARE_DYNAMIC_DELEGATE_OneParam(FOnLoadGameItemClicked, ULoadGameItem*, ClickedLoadGameItem);

public:
	UFUNCTION(BlueprintCallable, Category = "FastMenuPlugin")
	void SetSavedGameNameText(const FText& SavedGameName);

	UFUNCTION(BlueprintCallable, Category = "FastMenuPlugin")
	void SetTimestampText(const FText& Timestamp);

	FORCEINLINE class UButton* GetItemButton() { return ItemButton; }

	void SetActive();

	void SetInactive();

	FText GetSavedGameName();

public:
	UPROPERTY()
	FOnLoadGameItemClicked OnLoadGameItemClicked;

	UPROPERTY(BlueprintReadWrite, Category = "FastMenuPlugin")
	FSlateBrush NormalItemButtonStyle;

	UPROPERTY(BlueprintReadWrite, Category = "FastMenuPlugin")
	FSlateBrush HoveredItemButtonStyle;

	UPROPERTY(BlueprintReadWrite, Category = "FastMenuPlugin")
		FText CreatedTimestampText {
		FText()
	};

	UPROPERTY(BlueprintReadWrite, Category = "FastMenuPlugin")
		FText UpdatedTimestampText {
		FText()
	};

protected:
	virtual void NativeConstruct();

private:
	UFUNCTION()
	void HandleItemButtonClicked();

private:
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "FastMenuPlugin")
		class UTextBlock* SavedGameNameText;

	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "FastMenuPlugin")
		UTextBlock* TimestampText;

	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "FastMenuPlugin")
		UButton* ItemButton;
};
