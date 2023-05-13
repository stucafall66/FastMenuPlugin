// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGamePage/SaveGameItem.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"


void USaveGameItem::NativeConstruct()
{
	// Set Hovered Style & Normal Style
	NormalItemButtonStyle = ItemButton->WidgetStyle.Normal;
	HoveredItemButtonStyle = ItemButton->WidgetStyle.Hovered;

	ItemButton->OnClicked.AddDynamic(this, &ThisClass::HandleItemButtonClicked);
	DeleteButton->OnClicked.AddDynamic(this, &ThisClass::HandleDeleteButtonClicked);
}

void USaveGameItem::SetSavedGameNameText(const FText& SavedGameName)
{
	SavedGameNameText->SetText(SavedGameName);
}

void USaveGameItem::SetTimestampText(const FText& Timestamp)
{
	TimestampText->SetText(Timestamp);
}

void USaveGameItem::SetActive()
{
	// Set all brushes to hovered style
	FButtonStyle ActiveStyle;
	ActiveStyle.SetNormal(HoveredItemButtonStyle);
	ActiveStyle.SetHovered(HoveredItemButtonStyle);
	ActiveStyle.SetPressed(HoveredItemButtonStyle);
	ActiveStyle.SetNormalPadding(FMargin(12.f, 1.5f));
	ActiveStyle.SetPressedPadding(FMargin(12.f, 1.5f));
	ItemButton->SetStyle(ActiveStyle);
}

void USaveGameItem::SetInactive()
{
	// Set Normal brush to normal style, other brushes to hovered style
	FButtonStyle ActiveStyle;
	ActiveStyle.SetNormal(NormalItemButtonStyle);
	ActiveStyle.SetHovered(HoveredItemButtonStyle);
	ActiveStyle.SetPressed(HoveredItemButtonStyle);
	ActiveStyle.SetNormalPadding(FMargin(12.f, 1.5f));
	ActiveStyle.SetPressedPadding(FMargin(12.f, 1.5f));
	ItemButton->SetStyle(ActiveStyle);
}

void USaveGameItem::HandleItemButtonClicked()
{
	if (!IsDesignTime())
	{
		OnSaveGameItemClicked.ExecuteIfBound(this);
	}
}

void USaveGameItem::HandleDeleteButtonClicked()
{
	if (!IsDesignTime())
	{
		UE_LOG(LogTemp, Warning, TEXT("Delete Button Clicked"));
		OnDeleteSaveGameClicked.ExecuteIfBound(this);
	}
}

FText USaveGameItem::GetSavedGameName()
{
	if (SavedGameNameText != nullptr)
	{
		return SavedGameNameText->GetText();
	}
	else
	{
		return FText();
	}
}
