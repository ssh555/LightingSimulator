// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "StringTableToolFunctionLibrary.generated.h"

class UStringTable;

/**
 * 
 */
UCLASS()
class LIGHTINGSIMULATOR_API UStringTableToolFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/// <summary>
	/// ���� pak,ֻ��Ҫ�����ļ�����
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "StringTableTool")
	static UStringTable* GetStringTableFromFile(UObject* Outer, FString FileName);

	/// <summary>
	/// ���� pak,ֻ��Ҫ�����ļ�����
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "StringTableTool")
	static FName GetStringTableID(FString FileName);

};
