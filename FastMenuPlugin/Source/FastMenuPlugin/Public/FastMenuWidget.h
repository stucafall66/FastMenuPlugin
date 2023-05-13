// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FastMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class FASTMENUPLUGIN_API UFastMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "FastMenuPlugin")
	void ResumeGame();

	UFUNCTION(BlueprintCallable, Category = "FastMenuPlugin")
	void ProcessMenuLogic(bool Open);

public:
	UPROPERTY(BlueprintReadWrite, Category = "FastMenuPlugin")
	bool IsMenuOpened{false};

protected:
	virtual bool Initialize() override;

private:
	UFUNCTION()
	void OnResumeBtnClicked();

private:
	/*UPROPERTY(meta = (BindWidget))
	class UButton* ResumeBtn;*/
};
