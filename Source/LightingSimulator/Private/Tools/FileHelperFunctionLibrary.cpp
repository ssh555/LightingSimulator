// Fill out your copyright notice in the Description page of Project Settings.


#include "Tools/FileHelperFunctionLibrary.h"
#include <HAL/PlatformFilemanager.h>
#include <GenericPlatform/GenericPlatformFile.h>

TArray<FString> UFileHelperFunctionLibrary::GetAllFiles(FString FilePath, bool IsContainChildDir, FString filter)
{
	IFileManager& FileManager = IFileManager::Get();
	TArray<FString> ret;
	if (IsContainChildDir) {
		FileManager.FindFilesRecursive(ret, *(FilePath), *filter, true, false);
		filter = FilePath.TrimChar('*');
		TArray<FString> removeList;
		for (FString tmp : ret)
		{
			if (!tmp.Contains(filter)) {
				removeList.Add(tmp);
			}
		}
		for (FString tmp : removeList) {
			ret.Remove(tmp);
		}
	}
	else {
		FileManager.FindFiles(ret, *(FilePath), *filter);
	}
	return ret;
}

bool UFileHelperFunctionLibrary::DeleteDirectory(FString DirPath)
{
	IFileManager& FileManager = IFileManager::Get();
	return FileManager.DeleteDirectory(*DirPath, true, true);
}

bool UFileHelperFunctionLibrary::CopyFile(FString FilePath, FString ToFilePath)
{
	FPlatformFileManager& PFM = FPlatformFileManager::Get();
	return PFM.GetPlatformFile().CopyFile(*ToFilePath, *FilePath);
}

bool UFileHelperFunctionLibrary::DeleteFile(FString FilePath)
{
	IFileManager& FileManager = IFileManager::Get();
	return FileManager.Delete(*FilePath, true, true);
}

bool UFileHelperFunctionLibrary::RenameFile(FString FilePath, FString newName)
{
	int index;
	FString newPath = FilePath;
	newPath.FindLastChar('/', index);
	newPath = newPath.Replace(*(FilePath.Right(FilePath.Len() - index - 1)), *newName);

	return MoveFile(FilePath, newPath);
}

bool UFileHelperFunctionLibrary::MoveFile(FString From, FString To)
{
	IFileManager& FileManager = IFileManager::Get();
	return FileManager.Move(*To, *From);
}

bool UFileHelperFunctionLibrary::FileExist(FString FilePath)
{
	IFileManager& FileManager = IFileManager::Get();
	return FileManager.FileExists(*FilePath);
}
