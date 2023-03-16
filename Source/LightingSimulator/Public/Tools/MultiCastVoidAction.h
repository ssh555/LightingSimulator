// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MultiCastVoidAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMultiCastAction);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class LIGHTINGSIMULATOR_API UMultiCastVoidAction : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable, BlueprintReadOnly, BlueprintCallable)
	FMultiCastAction MultiCastAction;
};
