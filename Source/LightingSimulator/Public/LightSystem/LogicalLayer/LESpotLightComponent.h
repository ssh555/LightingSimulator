// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SpotLightComponent.h"
#include "SaveAndLoadData.h"
#include "LESpotLightComponent.generated.h"

class UStringTable;

/**
 * 
 */
UCLASS()
class LIGHTINGSIMULATOR_API ULESpotLightComponent : public USpotLightComponent, public ISaveAndLoadData
{
	GENERATED_BODY()
protected:
	//UStringTable* StrTable;


public:


	virtual FString GetData(const FString& key) override;


	//virtual TArray<FString> GetAllDatas(const int deepth) override;


	virtual void SetData(FString& key, FString& value) override;


};
