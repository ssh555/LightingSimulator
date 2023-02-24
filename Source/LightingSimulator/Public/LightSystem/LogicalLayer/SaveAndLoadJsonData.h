// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SaveAndLoadJsonData.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))
class USaveAndLoadJsonData : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LIGHTINGSIMULATOR_API ISaveAndLoadJsonData
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, Category = "SaveAndLoad")
	virtual TArray<FString> GetDataAsJson(const int deepth);

	UFUNCTION(BlueprintCallable, Category = "SaveAndLoad")
	virtual void SetDataFromJson(TArray<FString> dataStrList, int& deepth);
};
