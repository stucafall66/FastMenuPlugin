// Fill out your copyright notice in the Description page of Project Settings.


#include "FastMenuWidget.h"
#include "Components/Button.h"
#include "Engine.h"

void UFastMenuWidget::ResumeGame()
{
	RemoveFromParent();
	ProcessMenuLogic(false);
}

void UFastMenuWidget::ProcessMenuLogic(bool Open)
{
	APlayerController* LocalPlayerController = 
		Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	if (Open)//Is opening menu
	{
		//Show cursor in order to click menu buttons
		FInputModeGameAndUI Mode;
		Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		Mode.SetWidgetToFocus(TakeWidget());
		LocalPlayerController->SetInputMode(Mode);
		LocalPlayerController->SetShowMouseCursor(true);
		// Pause the first local player
		LocalPlayerController->SetPause(true);
		IsMenuOpened = true;
	}
	else
	{
		// Reset cursor
		FInputModeGameOnly Mode;
		LocalPlayerController->SetInputMode(Mode);
		// LocalPlayerController->SetShowMouseCursor(false);
		// UnPause the first local player
		LocalPlayerController->SetPause(false);
		
		IsMenuOpened = false;
	}
}

bool UFastMenuWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	/*if (ResumeBtn)
	{
		ResumeBtn->OnClicked.AddDynamic(this, &ThisClass::OnResumeBtnClicked);
	}*/
	return true;
}

void UFastMenuWidget::OnResumeBtnClicked()
{
	ResumeGame();
}
