// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ContentPageBase.h"
#include "SettingStructures.h"
#include "ContentVideo.generated.h"

/**
 * 
 */
UCLASS()
class FASTMENUPLUGIN_API UContentVideo : public UContentPageBase
{
	GENERATED_BODY()

public:
	virtual void ApplyChanges() override;

protected:
	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnVideoResolutionChange(FName SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnFullscreenChange(bool bIsChecked);

	UFUNCTION()
	void OnShadowQualityChange(FName SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnPostProcessingChange(FName SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnTextureQualityChange(FName SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnMaterialQualityChange(FName SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnAntiAliasingChange(FName SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnEffectChange(FName SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnDetailModeChange(FName SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnViewDistanceChange(FName SelectedItem, ESelectInfo::Type SelectionType);

	void SaveChanges();

	UFUNCTION(BlueprintCallable, Category = "FastMenuPlugin")
	void RestoreDefault();

	void SetupComboBoxes();

private:
	UPROPERTY()
	FName VideoResolution{ FName(TEXT("1920x1080")) };

	UPROPERTY()
	bool Fullscreen{ true };

	UPROPERTY()
	EComboBoxOption ShadowQuality{ EComboBoxOption::Epic };

	UPROPERTY()
	EComboBoxOption PostProcessing{ EComboBoxOption::Epic };

	UPROPERTY()
	EComboBoxOption TextureQuality{ EComboBoxOption::Epic };

	UPROPERTY()
	EComboBoxOption MaterialQuality{ EComboBoxOption::Epic };

	UPROPERTY()
	EComboBoxOption AntiAliasing{ EComboBoxOption::Epic };

	UPROPERTY()
	EComboBoxOption Effect{ EComboBoxOption::Epic };

	UPROPERTY()
	EComboBoxOption DetailMode{ EComboBoxOption::Epic };

	UPROPERTY()
	EComboBoxOption ViewDistance{ EComboBoxOption::Long };

	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "FastMenuPlugin")
	class UFastMenuComboBoxKey* VideoResolution_FastMenuComboBoxKey;

	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "FastMenuPlugin")
	class UCheckBox* Fullscreen_CheckBox;

	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "FastMenuPlugin")
	UFastMenuComboBoxKey* ShadowQuality_FastMenuComboBoxKey;

	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "FastMenuPlugin")
	UFastMenuComboBoxKey* PostProcessing_FastMenuComboBoxKey;

	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "FastMenuPlugin")
	UFastMenuComboBoxKey* TextureQuality_FastMenuComboBoxKey;

	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "FastMenuPlugin")
	UFastMenuComboBoxKey* MaterialQuality_FastMenuComboBoxKey;

	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "FastMenuPlugin")
	UFastMenuComboBoxKey* AntiAliasing_FastMenuComboBoxKey;

	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "FastMenuPlugin")
	UFastMenuComboBoxKey* Effect_FastMenuComboBoxKey;

	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "FastMenuPlugin")
	UFastMenuComboBoxKey* DetailMode_FastMenuComboBoxKey;

	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "FastMenuPlugin")
	UFastMenuComboBoxKey* ViewDistance_FastMenuComboBoxKey;
};
