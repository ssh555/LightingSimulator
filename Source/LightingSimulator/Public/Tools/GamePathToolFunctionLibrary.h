// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GamePathToolFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTINGSIMULATOR_API UGamePathToolFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/// <summary>
	/// //InstallDir/WindowsNoEditor/GameName/Binaries/Win64/
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "Paths", BlueprintPure)
	static FString GetBaseDir();

	/// <summary>
	/// //InstallDir/WindowsNoEditor/
	/// </summary>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable, Category = "Paths", BlueprintPure)
	static FString GetRootDir();

	/// <summary>
	/// InstallDir/WindowsNoEditor/GameName/
	/// </summary>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable, Category = "Paths", BlueprintPure)
	static FString GetGameDir();

	/// <summary>
	/// InstallDir/WindowsNoEditor/GameName/Content/
	/// </summary>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable, Category = "Paths", BlueprintPure)
	static FString GetGameContentDir();
	
	/// <summary>
	/// InstallDir/WindowsNoEditor/GameName/Saved/
	/// </summary>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable, Category = "Paths", BlueprintPure)
	static FString GetGameSavedDir();

	/// <summary>
	/// InstallDir/WindowsNoEditor/GameName/Saved/Logs/
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "Paths", BlueprintPure)
	static FString GetGameSavedLogDir();

	/// <summary>
	/// InstallDir/WindowsNoEditor/GameName/Content/CSV/
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "Paths", BlueprintPure)
	static FString GetGameContentCSVDir();

	/// <summary>
	/// InstallDir/WindowsNoEditor/GameName/Content/JSON/
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "Paths", BlueprintPure)
		static FString GetGameContentJSONDir();
};
