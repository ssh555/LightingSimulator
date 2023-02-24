// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSystem/LogicalLayer/SaveAndLoadJsonData.h"

// Add default functionality here for any ISaveAndLoadJsonData functions that are not pure virtual.


TArray<FString> ISaveAndLoadJsonData::GetDataAsJson(const int deepth)
{
	TArray<FString> ans;
	return ans;
}

void ISaveAndLoadJsonData::SetDataFromJson(TArray<FString> dataStrList, int& deepth)
{
	return;
}
