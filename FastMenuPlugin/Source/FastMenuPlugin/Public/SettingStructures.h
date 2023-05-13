#pragma once

#include "CoreMinimal.h"
#include "InputCoreTypes.h"
#include "SettingStructures.generated.h"

// Save Enum into Saved Game instead of FText
UENUM()
enum class EComboBoxOption : uint8
{
	Low,
	Medium,
	High,
	Epic,
	Short,
	Long,
	English,
	Chinese
};

USTRUCT()
struct FVideoContentSettings
{
	GENERATED_BODY()

	UPROPERTY()
	FName VideoResolution {FName("1920x1080")};

	UPROPERTY()
	bool Fullscreen{true};

	UPROPERTY()
	EComboBoxOption ShadowQuality {
		EComboBoxOption::Epic
	};

	UPROPERTY()
	EComboBoxOption PostProcessing {
		EComboBoxOption::Epic
	};

	UPROPERTY()
	EComboBoxOption TextureQuality {
		EComboBoxOption::Epic
	};

	UPROPERTY()
	EComboBoxOption MaterialQuality {
		EComboBoxOption::Epic
	};

	UPROPERTY()
	EComboBoxOption AntiAliasing {
		EComboBoxOption::Epic
	};

	UPROPERTY()
	EComboBoxOption Effect {
		EComboBoxOption::Epic
	};

	UPROPERTY()
	EComboBoxOption DetailMode {
		EComboBoxOption::Epic
	};

	UPROPERTY()
	EComboBoxOption ViewDistance {
		EComboBoxOption::Long
	};
};


USTRUCT()
struct FAudioContentSettings
{
	GENERATED_BODY()

	UPROPERTY()
	float MasterVolume{ 1.f };

	UPROPERTY()
	float SoundEffectVolume{ 1.f };

	UPROPERTY()
	float AmbientVolume{ 1.f };

	UPROPERTY()
	float MusicVolume{ 1.f };
};

USTRUCT(BlueprintType)
struct FControlContentSettings
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "FastMenuPlugin")
	FInputChord SetDestinationKey { FInputChord(FKey(FName("LeftMouseButton")), false, false, false, false) };

	UPROPERTY(BlueprintReadWrite, Category = "FastMenuPlugin")
	FInputChord ForwardKey { FInputChord(FKey(FName("W")), false, false, false, false) };

	UPROPERTY(BlueprintReadWrite, Category = "FastMenuPlugin")
	FInputChord BackwardKey { FInputChord(FKey(FName("S")), false, false, false, false) };

	UPROPERTY(BlueprintReadWrite, Category = "FastMenuPlugin")
	FInputChord LeftKey { FInputChord(FKey(FName("A")), false, false, false, false) };

	UPROPERTY(BlueprintReadWrite, Category = "FastMenuPlugin")
	FInputChord RightKey { FInputChord(FKey(FName("D")), false, false, false, false) };
};

USTRUCT(BlueprintType)
struct FMiscellaneousContentSettings
{
	GENERATED_BODY()

	UPROPERTY()
	EComboBoxOption Language {
		EComboBoxOption::English
	};
};