// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PointLightComponent.h"
#include "SaveAndLoadJsonData.h"
#include "LEPointLightComponent.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTINGSIMULATOR_API ULEPointLightComponent : public UPointLightComponent, public ISaveAndLoadJsonData
{
	GENERATED_BODY()
	
public:
	virtual TArray<FString> GetDataAsJson(const int deepth) override;

	virtual void SetDataFromJson(TArray<FString> dataStrList, int& deepth) override;

};
