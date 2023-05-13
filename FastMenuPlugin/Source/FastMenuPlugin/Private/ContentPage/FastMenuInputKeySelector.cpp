// Fill out your copyright notice in the Description page of Project Settings.


#include "ContentPage/FastMenuInputKeySelector.h"
//#include "Framework/Commands/InputChord.h"

UFastMenuInputKeySelector::UFastMenuInputKeySelector()
{
	OnKeySelected.AddDynamic(this, &ThisClass::HandleInputKeySelected);
}

void UFastMenuInputKeySelector::HandleInputKeySelected(FInputChord PressedKey)
{
	UE_LOG(LogTemp, Warning, TEXT("SelectedKey is %s"), *PressedKey.GetInputText().ToString() );
	//ChosenKey = FName(*PressedKey.GetInputText().ToString());
}

