// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSystem/LogicalLayer/LETimeline.h"
#include "Tools/GamePathToolFunctionLibrary.h"
#include "LightSystem/LogicalLayer/LightEntityHelper.h"
#include "LightSystem/LogicalLayer/LEOpFile.h"
#include "Tools/FileHelperFunctionLibrary.h"

LETimeline::LETimeline()
{
	Reset();
}

LETimeline::~LETimeline()
{
}

void LETimeline::SetFile(FString fileName, USceneComponent* comp)
{
	if (!fileName.Contains(".letl")) {
		fileName.Append(".letl");
	}
	this->FileName = fileName;
	fileName = UGamePathToolFunctionLibrary::GetGameLETimeline().Append(fileName);
	if (UFileHelperFunctionLibrary::FileExist(fileName)) {
		FFileHelper::LoadFileToStringArray(this->StringData, *(fileName));
	}
	this->OwnComp = comp;
}

void LETimeline::Run(float DeltaTime)
{
	if (this->curRow >= this->StringData.Num())
	{
		if (this->bIsAutoReset && this->curRow != 0)
		{
			this->Reset();
		}
		else
		{
			return;
		}
	}
	this->curTickTime += DeltaTime;
	FString key, value;
	ULightEntityHelper::StrStrParsor(this->StringData[this->curRow], key, value);
	float _time = FCString::Atof(*key);
	if (this->curTickTime >= _time) {
		++(this->curRow);
		LEOpFile tickFile;
		tickFile.SetFile(value, this->OwnComp);
		//tickFile.Run(DeltaTime);
		tickFile.Execute();
	}
}

void LETimeline::Reset()
{
	this->curTickTime = 0.0f;
	this->curRow = 0;
}
