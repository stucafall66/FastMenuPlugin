// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameStructure.h"

void USaveGameStructure::SetCreatedTimeText(const FText& DateTimeText)
{
	CreatedTimeText = DateTimeText;
}

void USaveGameStructure::SetUpdatedTimeText(const FText& DateTimeText)
{
	UpdatedTimeText = DateTimeText;
}
