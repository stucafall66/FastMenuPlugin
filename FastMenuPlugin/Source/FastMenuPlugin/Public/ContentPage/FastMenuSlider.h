// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FastMenuSlider.generated.h"

/**
 * 
 */
UCLASS()
class FASTMENUPLUGIN_API UFastMenuSlider : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "FastMenuPlugin")
	class USlider* Slider;
};
