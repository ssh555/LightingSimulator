// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/DirectionalLightComponent.h"
#include "SaveAndLoadData.h"
#include "LEDirectionalLightComponent.generated.h"

class UStringTable;

/**
 * 
 */
UCLASS()
class LIGHTINGSIMULATOR_API ULEDirectionalLightComponent : public UDirectionalLightComponent, public ISaveAndLoadData
{
	GENERATED_BODY()

public:

	virtual FString GetData(const FString& key) override;

	virtual void SetData(FString& key, FString& value) override;



};
