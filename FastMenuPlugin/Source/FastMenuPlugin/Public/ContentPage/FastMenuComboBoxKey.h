// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ComboBoxKey.h"
#include "FastMenuComboBoxKey.generated.h"

/**
 * 
 */
UCLASS()
class FASTMENUPLUGIN_API UFastMenuComboBoxKey : public UComboBoxKey
{
	GENERATED_BODY()

public:
	UFastMenuComboBoxKey();

	UFUNCTION(BlueprintImplementableEvent, Category = "FastMenuPlugin")
	UWidget* OnGenerateContentWidgetCallback(FName Item);

	UFUNCTION(BlueprintImplementableEvent, Category = "FastMenuPlugin")
	UWidget* OnGenerateItemWidgetCallback(FName Item);
};
