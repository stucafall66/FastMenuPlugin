// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameStructure.generated.h"

/**
 * 
 */
UCLASS()
class USaveGameStructure : public USaveGame
{
	GENERATED_BODY()

public:
	void SetCreatedTimeText(const FText& DateTimeText);
	void SetUpdatedTimeText(const FText& DateTimeText);

	FORCEINLINE FText GetCreatedTimeText() { return CreatedTimeText; }
	FORCEINLINE FText GetUpdatedTimeText() { return UpdatedTimeText; }

private:
	UPROPERTY()
	FText CreatedTimeText { FText() };

	UPROPERTY()
	FText UpdatedTimeText { FText() };
};
