// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LightEntityHelper.generated.h"

class ALightEntity;

/**
 * 
 */
UCLASS()
class LIGHTINGSIMULATOR_API ULightEntityHelper : public UObject
{
	GENERATED_BODY()

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
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LightEntity|StringTools")
	static void StrStrParsor(const FString& str, FString& key, FString& value);

	/// <summary>
	/// 组合为 "key" : "value" 格式
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LightEntity|StringTools")
	static FString StrStrUnParsor(FString key, FString value, int tabNum = 0);

	/// <summary>
	/// 根据 ClassType 生成对应的 UObject
	/// 只有特定的一些预设可以生成
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LightEntity|ClassTools")
	static USceneComponent* CreateSubobject(UObject* obj, FString ClassType);



protected:
	TMap<FString, ALightEntity*> LightEntityMaps;

public:
	/// <summary>
	/// 只需要传入文件名称，会在方法内部补全路径，即指定路径
	/// </summary>
	bool LoadDataFromJsonFile(ALightEntity* LEData, FString FileName);
	
	/// <summary>
	/// 只需要传入文件名称，会在方法内部补全路径，即指定路径
	/// </summary>
	bool SaveDataToJsonFile(ALightEntity* LEData, FString FileName);

};
