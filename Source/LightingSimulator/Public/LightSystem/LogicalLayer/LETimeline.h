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
	// ��Ӧ�ļ�����
	FString FileName;

	// ���ж���
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
