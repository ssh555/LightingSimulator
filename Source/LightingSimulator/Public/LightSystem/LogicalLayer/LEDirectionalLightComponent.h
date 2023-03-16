// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/DirectionalLightComponent.h"
#include "SaveAndLoadData.h"
#include "LEOperationInterface.h"
#include "LEDirectionalLightComponent.generated.h"

class UStringTable;

/**
 * 
 */
UCLASS(ClassGroup = (LightEntity), meta = (BlueprintSpawnableComponent))
class LIGHTINGSIMULATOR_API ULEDirectionalLightComponent : public UDirectionalLightComponent, public ISaveAndLoadData, public ILEOperationInterface
{
	GENERATED_BODY()

public:
	ULEDirectionalLightComponent();
	virtual FString GetData(const FString& key) override;

	virtual void SetData(const FString& key, const FString& value) override;


	virtual void BeginPlay() override;


	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
