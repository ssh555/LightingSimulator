// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/RectLightComponent.h"
#include "SaveAndLoadJsonData.h"
#include "LERectLightComponent.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTINGSIMULATOR_API ULERectLightComponent : public URectLightComponent, public ISaveAndLoadJsonData
{
	GENERATED_BODY()
	
public:
	virtual TArray<FString> GetDataAsJson(const int deepth) override;

	virtual void SetDataFromJson(TArray<FString> dataStrList, int& deepth) override;

};
