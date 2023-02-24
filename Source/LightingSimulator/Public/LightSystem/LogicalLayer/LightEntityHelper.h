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
	/// ���� string
	/// string �� <key, value> ��ʽΪ "key" : " value"
	/// :���Ϊkey,�Ҳ�Ϊvalue, ����ʱ�Զ�ȥ�������"�Ϳո�
	/// ���Ҳ���:��ֱ�ӷ���key = str, value = "
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LightEntity|StringTools")
	static void StrStrParsor(const FString& str, FString& key, FString& value);

	/// <summary>
	/// ���Ϊ "key" : "value" ��ʽ
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LightEntity|StringTools")
	static FString StrStrUnParsor(FString key, FString value, int tabNum = 0);

	/// <summary>
	/// ���� ClassType ���ɶ�Ӧ�� UObject
	/// ֻ���ض���һЩԤ���������
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LightEntity|ClassTools")
	static USceneComponent* CreateSubobject(UObject* obj, FString ClassType);



protected:
	TMap<FString, ALightEntity*> LightEntityMaps;

public:
	/// <summary>
	/// ֻ��Ҫ�����ļ����ƣ����ڷ����ڲ���ȫ·������ָ��·��
	/// </summary>
	bool LoadDataFromJsonFile(ALightEntity* LEData, FString FileName);
	
	/// <summary>
	/// ֻ��Ҫ�����ļ����ƣ����ڷ����ڲ���ȫ·������ָ��·��
	/// </summary>
	bool SaveDataToJsonFile(ALightEntity* LEData, FString FileName);

};
