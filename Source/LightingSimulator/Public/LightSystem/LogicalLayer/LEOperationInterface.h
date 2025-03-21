// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LEOperationInterface.generated.h"

class LEOpFile;
class LETimeline;

// This class does not need to be modified.
UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint), Blueprintable, BlueprintType)
class ULEOperationInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LIGHTINGSIMULATOR_API ILEOperationInterface
{
	GENERATED_BODY()
protected:
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.

public:
	LEOpFile* TickFile;

	LETimeline* TimeFile;

	void InitFile();

	virtual void Update(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);
};
