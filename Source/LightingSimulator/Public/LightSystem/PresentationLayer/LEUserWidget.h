// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LEUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTINGSIMULATOR_API ULEUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;


	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;





	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

};
