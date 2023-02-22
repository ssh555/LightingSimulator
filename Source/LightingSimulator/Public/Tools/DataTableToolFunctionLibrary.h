// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DataTableToolFunctionLibrary.generated.h"

class UDataTable;

/**
 * 
 */
UCLASS()
class LIGHTINGSIMULATOR_API UDataTableToolFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
// 动态读取DataTable数据表格
#pragma region 
	UFUNCTION(BlueprintCallable, DisplayName = "Fill Data Table from CSV String", Category = "DataTable")
	static bool FillDataTableFromCSVString(UDataTable* DataTable, const FString& CSVString);

	UFUNCTION(BlueprintCallable, DisplayName = "Fill Data Table from CSV File", Category = "DataTable")
	static bool FillDataTableFromCSVFile(UDataTable* DataTable, const FString& CSVFilePath);

	UFUNCTION(BlueprintCallable, DisplayName = "Fill Data Table from JSON String", Category = "DataTable")
	static bool FillDataTableFromJSONString(UDataTable* DataTable, const FString& JSONString);

	UFUNCTION(BlueprintCallable, DisplayName = "Fill Data Table from JSON File", Category = "DataTable")
	static bool FillDataTableFromJSONFile(UDataTable* DataTable, const FString& JSONFilePath);

	UFUNCTION(BlueprintCallable, DisplayName = "Get Table As CSV String", Category = "DataTable")
	static void GetDataTableAsCSVString(UDataTable* DataTable, FString& CSVString);

	UFUNCTION(BlueprintCallable, DisplayName = "Get Table As CSV File", Category = "DataTable")
	static void GetDataTableAsCSVFile(UDataTable* DataTable, const FString& CSVFilePath);

	UFUNCTION(BlueprintCallable, DisplayName = "Get Table As JSON String", Category = "DataTable")
	static void GetDataTableAsJSONString(UDataTable* DataTable, FString& JSONString);

	UFUNCTION(BlueprintCallable, DisplayName = "Get Table As JSON File", Category = "DataTable")
	static void GetDataTableAsJSONFile(UDataTable* DataTable, const FString& JSONFilePath);
#pragma endregion


};
