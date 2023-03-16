// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSystem/LogicalLayer/SaveAndLoadData.h"
#include <Kismet/KismetStringTableLibrary.h>
#include "LightSystem/LogicalLayer/LightEntityHelper.h"
#include <Internationalization/StringTable.h>
#include <Tools/StringTableToolFunctionLibrary.h>

// Add default functionality here for any ISaveAndLoadData functions that are not pure virtual.

FString ISaveAndLoadData::GetData(const FString& key)
{
	return "";
}

TArray<FString> ISaveAndLoadData::GetAllDatas(const int deepth)
{
	TArray<FString> ans;

	TArray<FString> keys = UKismetStringTableLibrary::GetKeysFromStringTable(this->GetStrTable()->GetStringTableId());
	for (FString key : keys)
	{
		ans.Add(ULightEntityHelper::StrStrUnParsor(key, this->GetData(key), deepth));
	}

	return ans;
}

void ISaveAndLoadData::SetData(const FString& key, const FString& value)
{
	return;
}

UStringTable* ISaveAndLoadData::GetStrTable()
{
	if (this->StrTable == nullptr) {
		UObject* obj = Cast<UObject>(this);
		this->StrTable = UStringTableToolFunctionLibrary::GetStringTableFromFile(obj, obj->GetClass()->GetName());
	}
	return this->StrTable;
}

