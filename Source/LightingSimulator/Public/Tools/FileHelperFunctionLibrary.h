// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FileHelperFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTINGSIMULATOR_API UFileHelperFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "FileHelper|Directory")
	static bool DeleteDirectory(FString DirPath);



	UFUNCTION(BlueprintCallable, Category = "FileHelper|File")
	static TArray<FString> GetAllFiles(FString FilePath, bool IsContainChildDir, FString filter = "");

	UFUNCTION(BlueprintCallable, Category = "FileHelper|File")
	static bool CopyFile(FString FilePath, FString ToFilePath);

	UFUNCTION(BlueprintCallable, Category = "FileHelper|File")
	static bool DeleteFile(FString FilePath);

	UFUNCTION(BlueprintCallable, Category = "FileHelper|File")
	static bool RenameFile(FString FilePath, FString newName);

	UFUNCTION(BlueprintCallable, Category = "FileHelper|File")
	static bool MoveFile(FString From, FString To);

	UFUNCTION(BlueprintCallable, Category = "FileHelper|File", BlueprintPure)
	static bool FileExist(FString FilePath);
};
