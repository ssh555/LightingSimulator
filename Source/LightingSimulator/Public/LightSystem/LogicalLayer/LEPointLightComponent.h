// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PointLightComponent.h"
#include "SaveAndLoadData.h"
#include "LEPointLightComponent.generated.h"

class UStringTable;

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LIGHTINGSIMULATOR_API ULEPointLightComponent : public UPointLightComponent, public ISaveAndLoadData
{
	GENERATED_BODY()
protected:
	//UStringTable* StrTable;


public:

	virtual FString GetData(const FString& key) override;

	virtual void SetData(FString& key, FString& value) override;
};
