// Fill out your copyright notice in the Description page of Project Settings.


#include "Tools/StringTableToolFunctionLibrary.h"
#include <Internationalization/StringTable.h>
#include "Tools/GamePathToolFunctionLibrary.h"
#include <UObject/UObjectGlobals.h>


UStringTable* UStringTableToolFunctionLibrary::GetStringTableFromFile(UObject* Outer, FString FileName)
{
	return LoadObject<UStringTable>(Outer, *(UGamePathToolFunctionLibrary::GetGameLEStringTableDataDir() + FileName + "." + FileName));
}

FName UStringTableToolFunctionLibrary::GetStringTableID(FString FileName)
{
	//return GetStringTableFromFile(Outer, FileName)->GetStringTableId();
	return FName(*(UGamePathToolFunctionLibrary::GetGameLEStringTableDataDir() + FileName + "." + FileName));
}
