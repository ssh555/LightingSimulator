// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/RectLightComponent.h"
#include "SaveAndLoadData.h"
#include "LERectLightComponent.generated.h"

class UStringTable;

/**
 * 
 */
UCLASS()
class LIGHTINGSIMULATOR_API ULERectLightComponent : public URectLightComponent, public ISaveAndLoadData
{
	GENERATED_BODY()
protected:
	//UStringTable* StrTable;


public:


	virtual FString GetData(const FString& key) override;


	virtual void SetData(FString& key, FString& value) override;



};
