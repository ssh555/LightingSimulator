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

	// First build array of properties
	TArray<FProperty*> StructProps;
	for (TFieldIterator<FProperty> It(DataTable->RowStruct); It; ++It)
	{
		FProperty* Prop = *It;
		check(Prop != nullptr);
		StructProps.Add(Prop);
	}

	// First row, column titles, taken from properties
	CSVString += TEXT("---");
	for (int32 PropIdx = 0; PropIdx < StructProps.Num(); PropIdx++)
	{
		CSVString += TEXT(",");
		CSVString += StructProps[PropIdx]->GetName();
	}
	CSVString += TEXT("\n");

	// Now iterate over rows
	for (auto RowIt = DataTable->GetRowMap().CreateConstIterator(); RowIt; ++RowIt)
	{
		FName RowName = RowIt.Key();
		CSVString += RowName.ToString();

		uint8* RowData = RowIt.Value();
		for (int32 PropIdx = 0; PropIdx < StructProps.Num(); PropIdx++)
		{
			CSVString += TEXT(",");
			CSVString += DataTableUtils::GetPropertyValueAsString(StructProps[PropIdx], RowData, EDataTableExportFlags::None);
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
	FFileHelper::SaveStringToFile(CSVString, *CSVFilePath, FFileHelper::EEncodingOptions::ForceUTF8);
}
