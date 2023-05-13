// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ContentPageBase.generated.h"

/**
 * 
 */
UCLASS()
class FASTMENUPLUGIN_API UContentPageBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "FastMenuPlugin")
	virtual void ApplyChanges();
};
