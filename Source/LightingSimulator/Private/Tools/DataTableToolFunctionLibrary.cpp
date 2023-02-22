// Fill out your copyright notice in the Description page of Project Settings.


#include "Tools/DataTableToolFunctionLibrary.h"
#include <Engine/DataTable.h>

bool UDataTableToolFunctionLibrary::FillDataTableFromCSVString(UDataTable* DataTable, const FString& CSVString)
{
	if (!DataTable || (CSVString.Len() == 0))
	{

		return false;
	}

	TArray<FString> Errors = DataTable->CreateTableFromCSVString(CSVString);
	if (Errors.Num())
	{
		// It has some error message
		return false;
	}
	return true;
}

bool UDataTableToolFunctionLibrary::FillDataTableFromCSVFile(UDataTable* DataTable, const FString& CSVFilePath)
{
	FString CSVString;
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*CSVFilePath))
	{
		// Supports all combination of ANSI/Unicode files and platforms.
		FFileHelper::LoadFileToString(CSVString, *CSVFilePath);
	}
	else
	{
		return false;
	}
	return FillDataTableFromCSVString(DataTable, CSVString);
}

bool UDataTableToolFunctionLibrary::FillDataTableFromJSONString(UDataTable* DataTable, const FString& JSONString)
{
	if (!DataTable || (JSONString.Len() == 0))
	{

		return false;
	}
	TArray<FString> Errors = DataTable->CreateTableFromJSONString(JSONString);
	if (Errors.Num())
	{
		return false;
	}
	return true;
}

bool UDataTableToolFunctionLibrary::FillDataTableFromJSONFile(UDataTable* DataTable, const FString& JSONFilePath)
{
	FString JSONString;
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*JSONFilePath))
	{
		// Supports all combination of ANSI/Unicode files and platforms.
		FFileHelper::LoadFileToString(JSONString, *JSONFilePath);
	}
	else
	{
		return false;
	}
	return FillDataTableFromJSONString(DataTable, JSONString);
}

void UDataTableToolFunctionLibrary::GetDataTableAsCSVString(UDataTable* DataTable, FString& CSVString)
{
	CSVString = FString();

	if (!DataTable || (DataTable->RowStruct == nullptr))
	{

		return;
	}

	TArray<TArray<FString>> DataTableRows = DataTable->GetTableData();
	DataTableRows[0][0] = DataTable->ImportKeyField;
	
	for (int32 row = 0; row < DataTableRows.Num(); ++row) {
		for (int32 col = 0; col < DataTableRows[row].Num(); ++col){
			CSVString += DataTableRows[row][col];
			CSVString += TEXT(",");
		}
		CSVString += TEXT("\n");
	}


}

void UDataTableToolFunctionLibrary::GetDataTableAsCSVFile(UDataTable* DataTable, const FString& CSVFilePath)
{
	FString CSVString;
	GetDataTableAsCSVString(DataTable, CSVString);
	if (CSVString.Len() == 0)
	{
		return;
	}
	FString str = CSVFilePath;
	str = str.ToLower();
	if (!str.Contains(".csv")) {
		str = CSVFilePath + ".csv";
	}
	else {
		str = CSVFilePath;
	}
	FFileHelper::SaveStringToFile(CSVString, *str, FFileHelper::EEncodingOptions::ForceUTF8);
}

void UDataTableToolFunctionLibrary::GetDataTableAsJSONString(UDataTable* DataTable, FString& JSONString)
{
	JSONString = FString();

	if (!DataTable || (DataTable->RowStruct == nullptr))
	{
		return;
	}
	JSONString = DataTable->GetTableAsJSON();
}

void UDataTableToolFunctionLibrary::GetDataTableAsJSONFile(UDataTable* DataTable, const FString& JSONFilePath)
{
	FString JSONString;
	GetDataTableAsJSONString(DataTable, JSONString);
	if (JSONString.Len() == 0)
	{
		return;
	}
	FString str = JSONFilePath;
	str = str.ToLower();
	if (!str.Contains(".json")) {
		str = JSONFilePath + ".json";
	}
	else {
		str = JSONFilePath;
	}
	FFileHelper::SaveStringToFile(JSONString, *str, FFileHelper::EEncodingOptions::ForceUTF8);
}
