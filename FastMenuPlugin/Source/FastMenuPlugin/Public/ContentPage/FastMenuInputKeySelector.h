// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InputKeySelector.h"
//#include "Framework/Commands/InputChord.h"
#include "FastMenuInputKeySelector.generated.h"

/**
 * 
 */
UCLASS()
class FASTMENUPLUGIN_API UFastMenuInputKeySelector : public UInputKeySelector
{
	GENERATED_BODY()

public:
	UFastMenuInputKeySelector();

	UFUNCTION()
	void HandleInputKeySelected(FInputChord PressedKey);

};
