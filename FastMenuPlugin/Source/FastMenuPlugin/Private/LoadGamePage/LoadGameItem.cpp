// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadGamePage/LoadGameItem.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void ULoadGameItem::NativeConstruct()
{
	// Set Hovered Style & Normal Style
	NormalItemButtonStyle = ItemButton->WidgetStyle.Normal;
	HoveredItemButtonStyle = ItemButton->WidgetStyle.Hovered;

	ItemButton->OnClicked.AddDynamic(this, &ThisClass::HandleItemButtonClicked);
}

void ULoadGameItem::SetSavedGameNameText(const FText& SavedGameName)
{
	SavedGameNameText->SetText(SavedGameName);
}

void ULoadGameItem::SetTimestampText(const FText& Timestamp)
{
	TimestampText->SetText(Timestamp);
}

void ULoadGameItem::SetActive()
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

void ULoadGameItem::SetInactive()
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

FText ULoadGameItem::GetSavedGameName()
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

void ULoadGameItem::HandleItemButtonClicked()
{
	if (!IsDesignTime())
	{
		OnLoadGameItemClicked.ExecuteIfBound(this);
	}
}
