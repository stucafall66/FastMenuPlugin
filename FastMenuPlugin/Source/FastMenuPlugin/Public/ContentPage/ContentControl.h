// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ContentPage/ContentPageBase.h"
#include "SettingStructures.h"
#include "ContentControl.generated.h"

/**
 * 
 */
UCLASS()
class FASTMENUPLUGIN_API UContentControl : public UContentPageBase
{
	GENERATED_BODY()
	
public:
	virtual void ApplyChanges() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "FastMenuPlugin")
	void ProcessInputKeyPanels();

	UFUNCTION(BlueprintImplementableEvent, Category = "FastMenuPlugin")
	void SetInputKeySelected();

public:
	UPROPERTY(BlueprintReadWrite, Category = "FastMenuPlugin")
		FInputChord CurrentSetDestinationKey {
		FInputChord(FKey(FName("LeftMouseButton")), false, false, false, false)
	};

	UPROPERTY(BlueprintReadWrite, Category = "FastMenuPlugin")
		FInputChord CurrentForwardKey {
		FInputChord(FKey(FName("W")), false, false, false, false)
	};

	UPROPERTY(BlueprintReadWrite, Category = "FastMenuPlugin")
		FInputChord CurrentBackwardKey {
		FInputChord(FKey(FName("S")), false, false, false, false)
	};

	UPROPERTY(BlueprintReadWrite, Category = "FastMenuPlugin")
		FInputChord CurrentLeftKey {
		FInputChord(FKey(FName("A")), false, false, false, false)
	};

	UPROPERTY(BlueprintReadWrite, Category = "FastMenuPlugin")
		FInputChord CurrentRightKey {
		FInputChord(FKey(FName("D")), false, false, false, false)
	};
	///////////
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget), Category = "FastMenuPlugin")
		class UTextBlock* SetDestinationKeyText;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget), Category = "FastMenuPlugin")
		UTextBlock* ForwardKeyText;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget), Category = "FastMenuPlugin")
		UTextBlock* BackwardKeyText;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget), Category = "FastMenuPlugin")
		UTextBlock* LeftKeyText;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget), Category = "FastMenuPlugin")
		UTextBlock* RightKeyText;

protected:
	virtual void NativeOnInitialized() override;

private:
	void SaveChanges();

	UFUNCTION(BlueprintPure, Category = "FastMenuPlugin")
	FControlContentSettings GetDefaultKeySettings();

	UFUNCTION(BlueprintCallable, Category = "FastMenuPlugin")
	void RestoreDefault();

private:
	
};
