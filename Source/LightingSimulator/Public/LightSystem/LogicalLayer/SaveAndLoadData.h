// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SaveAndLoadData.generated.h"

class UClass;
class UStringTable;

// This class does not need to be modified.
UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint), Blueprintable, BlueprintType)
class USaveAndLoadData : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LIGHTINGSIMULATOR_API ISaveAndLoadData
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.

private:
	UStringTable* StrTable;

public:

	UFUNCTION(BlueprintCallable, Category = "SaveAndLoad")
	virtual FString GetData(const FString& key);

	UFUNCTION(BlueprintCallable, Category = "SaveAndLoad")
	virtual TArray<FString> GetAllDatas(const int deepth);

	/// <summary>
	/// 不包括子组件数据
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "SaveAndLoad")
	virtual void SetData(const FString& key, const FString& value);

	virtual UStringTable* GetStrTable();

	FString MatPath = "None";

	UMaterialInstanceDynamic* MatInst;
};
