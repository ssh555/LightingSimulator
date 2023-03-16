// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/RectLightComponent.h"
#include "SaveAndLoadData.h"
#include "LEOperationInterface.h"
#include "LERectLightComponent.generated.h"

class UStringTable;

/**
 * 
 */
UCLASS(ClassGroup = (LightEntity), meta = (BlueprintSpawnableComponent))
class LIGHTINGSIMULATOR_API ULERectLightComponent : public URectLightComponent, public ISaveAndLoadData, public ILEOperationInterface
{
	GENERATED_BODY()
protected:
	//UStringTable* StrTable;


public:
	ULERectLightComponent();

	virtual FString GetData(const FString& key) override;


	virtual void SetData(const FString& key, const FString& value) override;


	virtual void BeginPlay() override;


	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
