// Copyright Epic Games, Inc. All Rights Reserved.

#include "FastMenuPluginBPLibrary.h"
#include "FastMenuPlugin.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"


UFastMenuPluginBPLibrary::UFastMenuPluginBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	
}

void UFastMenuPluginBPLibrary::RunFastMenu(const UObject* WorldContextObject, UFastMenuWidget* FastMenu, bool OpenWidget)
{
	// When press ESC, if FastMenu is not created, create fast menu and AddToViewPort. set FastMenu->IsMenuOpened to true
	// If Fast Menu is created, check FastMenu->IsMenuOpened
	// true: close menu then set FastMenu->IsMenuOpened to false
	// false: Add Menu to Viewport then set FastMenu->IsMenuOpened to true
	if (GEngine)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);

		if (OpenWidget)
		{
			UE_LOG(LogTemp, Warning, TEXT("Open Widget"));
			if (FastMenu != nullptr)
			{
				FastMenu->AddToViewport();\
				FastMenu->ProcessMenuLogic(true);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("FastMenu Is Empty"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Close Widget"));
			FastMenu->ResumeGame();
		}
	}
}
