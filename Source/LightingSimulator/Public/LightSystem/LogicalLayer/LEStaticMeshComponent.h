// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "SaveAndLoadData.h"
#include "LEStaticMeshComponent.generated.h"

//class UStringTable;

/**
 * 
 */
UCLASS()
class LIGHTINGSIMULATOR_API ULEStaticMeshComponent : public UStaticMeshComponent, public ISaveAndLoadData
{
	GENERATED_BODY()
	

public:

	virtual FString GetData(const FString& key) override;

	/// <summary>
	/// 不包括子组件数据
	/// </summary>
	/// <param name="deepth"></param>
	/// <returns></returns>
	//virtual TArray<FString> GetAllDatas(const int deepth) override;

	virtual void SetData(FString& key, FString& value) override;






};
