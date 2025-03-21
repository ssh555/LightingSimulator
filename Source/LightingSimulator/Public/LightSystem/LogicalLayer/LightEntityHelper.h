// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LightEntityHelper.generated.h"

class ALightEntity;
class ISaveAndLoadData;

/**
 * 
 */
UCLASS()
class LIGHTINGSIMULATOR_API ULightEntityHelper : public UObject
{
	GENERATED_BODY()

private:
	static int curNum;

protected:
	ULightEntityHelper();

	static ULightEntityHelper* Instance;

public:
	static ULightEntityHelper* GetInstance();

	static FString GetTabStr(const int num);

	/// <summary>
	/// 解析 string
	/// string 的 <key, value> 格式为 "key" : " value"
	/// :左侧为key,右侧为value, 返回时自动去除两侧的"和空格
	/// 若找不到:，直接返回key = str, value = "
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LightEntityHelper|StringTools")
	static void StrStrParsor(const FString& str, FString& key, FString& value);

	/// <summary>
	/// 组合为 "key" : "value" 格式
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LightEntityHelper|StringTools")
	static FString StrStrUnParsor(FString key, FString value, int tabNum = 0);

	/// <summary>
	/// 根据 ClassType 生成对应的 UObject
	/// 只有特定的一些预设可以生成
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LightEntityHelper|ClassTools")
	static USceneComponent* CreateSubobject(UObject* obj, FString ClassType);



protected:
	TMap<FString, ALightEntity*> LightEntityMaps;

	void LoadDataToISL(ISaveAndLoadData* ISLData, TArray<FString>& dataStrList, int& deepth);

	TArray<FString> SaveDataFromISL(ISaveAndLoadData* ISLData, const int deepth);


public:
	/// <summary>
	/// 只需要传入文件名称，会在方法内部补全路径，即指定路径
	/// </summary>
	bool LoadDataFromFile(ALightEntity* LEData, FString FileName);

	
	/// <summary>
	/// 只需要传入文件名称，会在方法内部补全路径，即指定路径
	/// </summary>
	bool SaveDataToFile(ALightEntity* LEData, FString FileName);


};
