// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ContentPage/ContentPageBase.h"
#include "SettingStructures.h"
#include "ContentMiscellaneous.generated.h"

/**
 * 
 */
UCLASS()
class FASTMENUPLUGIN_API UContentMiscellaneous : public UContentPageBase
{
	GENERATED_BODY()
public:
	virtual void ApplyChanges() override;

protected:
	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnLanguageChange(FName SelectedItem, ESelectInfo::Type SelectionType);

	void SaveChanges();

	void SetupComboBoxes();

	UFUNCTION(BlueprintCallable, Category = "FastMenuPlugin")
	void RestoreDefault();

private:
	EComboBoxOption Language{ EComboBoxOption::English };

	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "FastMenuPlugin")
	class UFastMenuComboBoxKey* Language_FastMenuComboBoxKey;
};
