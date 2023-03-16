// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class LIGHTINGSIMULATOR_API LETimeline
{
protected:
	float curTickTime;

	int curRow;

public:
	// 对应文件名称
	FString FileName;

	// 按行读入
	TArray<FString> StringData;

	bool bIsAutoReset = false;

	USceneComponent* OwnComp;

public:
	LETimeline();
	~LETimeline();

	void SetFile(FString fileName, USceneComponent* comp);

	void Run(float DeltaTime);

	void Reset();
};
