// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ContentPage/ContentPageBase.h"
#include "ContentAudio.generated.h"

/**
 * 
 */
UCLASS()
class FASTMENUPLUGIN_API UContentAudio : public UContentPageBase
{
	GENERATED_BODY()

public:
	virtual void ApplyChanges() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "FastMenuPlugin")
	void HandleVolumes();

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "FastMenuPlugin")
		class UFastMenuSlider* MasterVolumeSlider;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "FastMenuPlugin")
		class UFastMenuSlider* SoundEffectVolumeSlider;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "FastMenuPlugin")
		class UFastMenuSlider* AmbientVolumeSlider;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "FastMenuPlugin")
		class UFastMenuSlider* MusicVolumeSlider;

	UPROPERTY(BlueprintReadWrite, Category = "FastMenuPlugin")
	float MasterVolume{ 1.f };

	UPROPERTY(BlueprintReadWrite, Category = "FastMenuPlugin")
	float SoundEffectVolume{ 1.f };

	UPROPERTY(BlueprintReadWrite, Category = "FastMenuPlugin")
	float AmbientVolume{ 1.f };

	UPROPERTY(BlueprintReadWrite, Category = "FastMenuPlugin")
	float MusicVolume{ 1.f };

protected:
	virtual void NativeOnInitialized() override;

private:
	UFUNCTION(BlueprintCallable, Category = "FastMenuPlugin")
	void HandleMasterVolumeChange(float Value);

	UFUNCTION(BlueprintCallable, Category = "FastMenuPlugin")
	void HandleSoundEffectVolumeChange(float Value);

	UFUNCTION(BlueprintCallable, Category = "FastMenuPlugin")
	void HandleAmbientVolumeChange(float Value);

	UFUNCTION(BlueprintCallable, Category = "FastMenuPlugin")
	void HandleMusicVolumeChange(float Value);

	UFUNCTION(BlueprintCallable, Category = "FastMenuPlugin")
	void RestoreDefault();

	void SaveChanges();

private:
	

};
