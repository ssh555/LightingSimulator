// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSystem/PresentationLayer/LEUserWidget.h"
#include "LightSystem/LightStudioGameMode.h"
#include <Kismet/KismetSystemLibrary.h>
#include "LightSystem/PresentationLayer/LSCameraPawn.h"
#include <Components/SlateWrapperTypes.h>
#include <Kismet/GameplayStatics.h>

FReply ULEUserWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	//UKismetSystemLibrary::PrintString(this, FString("Down: ") + this->GetName());

		(this, EMouseCaptureMode::NoCapture);

	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

// UGameplayStatics::SetViewportMouseCaptureMode(this, EMouseCaptureMode::NoCapture);
FReply ULEUserWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	//UKismetSystemLibrary::PrintString(this, FString("Up: ") + this->GetName());

	UGameplayStatics::SetViewportMouseCaptureMode(this, EMouseCaptureMode::CaptureDuringMouseDown);

	return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
}

void ULEUserWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	//UKismetSystemLibrary::PrintString(this, FString("Leave: ") + this->GetName());

	UGameplayStatics::SetViewportMouseCaptureMode(this, EMouseCaptureMode::CaptureDuringMouseDown);
}


