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

	virtual void SetData(FString& key, FString& value) override;






};
