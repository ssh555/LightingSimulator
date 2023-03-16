// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSystem/LogicalLayer/LEOperationInterface.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Components/SceneComponent.h>
#include "LightSystem/LightStudioGameMode.h"
#include "LightSystem/LogicalLayer/LEOpFile.h"
#include <LightSystem/LogicalLayer/LETimeline.h>

void ILEOperationInterface::InitFile()
{
	this->TickFile = new LEOpFile();
	this->TickFile->bIsAutoReset = true;
	this->TimeFile = new LETimeline();
	this->TimeFile->bIsAutoReset = false;
}

// Add default functionality here for any ILEOperationInterface functions that are not pure virtual.

void ILEOperationInterface::Update(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (!ALightStudioGameMode::bIsStart || ALightStudioGameMode::bIsPause) {
		return;
	}
	if (this->TimeFile) {
		this->TimeFile->Run(DeltaTime);
	}
	if (this->TickFile) {
		this->TickFile->Run(DeltaTime);
	}
}
