// Fill out your copyright notice in the Description page of Project Settings.


#include "Tools/GamePathToolFunctionLibrary.h"

FString UGamePathToolFunctionLibrary::GetBaseDir()
{
	return FString(FPlatformProcess::BaseDir());
}

FString UGamePathToolFunctionLibrary::GetRootDir()
{
	return FPaths::ConvertRelativePathToFull(FPaths::RootDir());
}

FString UGamePathToolFunctionLibrary::GetGameDir()
{
	return FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
}

FString UGamePathToolFunctionLibrary::GetGameContentDir()
{
	return FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir());
}

FString UGamePathToolFunctionLibrary::GetGameSavedDir()
{
	return FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir());
}

FString UGamePathToolFunctionLibrary::GetGameSavedLogDir()
{
	return FPaths::ConvertRelativePathToFull(FPaths::ProjectLogDir());
}

FString UGamePathToolFunctionLibrary::GetGameContentCSVDir()
{
	return GetGameContentDir() + "CSV/";
}

FString UGamePathToolFunctionLibrary::GetGameContentJSONDir()
{
	return GetGameContentDir() + "JSON/";
}

FString UGamePathToolFunctionLibrary::GetGameLightEntityDataDir()
{
	return GetGameContentDir() + "LightEntityData/";
}

FString UGamePathToolFunctionLibrary::GetGameLEStringTableDataDir()
{
	return "/Game/LightingSimulator/LightSystem/LEDataTable/";
}
