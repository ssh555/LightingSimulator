// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSystem/LogicalLayer/LightEntityHelper.h"
#include "Tools/GamePathToolFunctionLibrary.h"
#include "LightSystem/LogicalLayer/SaveAndLoadJsonData.h"
#include "LightSystem/LogicalLayer/LightEntity.h"
#include <HAL/FileManager.h>
#include <Misc/FileHelper.h>
#include "LightSystem/LogicalLayer/LEDirectionalLightComponent.h"
#include <UObject/Object.h>
#include "LightSystem/LogicalLayer/LEStaticMeshComponent.h"
#include <LightSystem/LogicalLayer/LEPointLightComponent.h>
#include <LightSystem/LogicalLayer/LERectLightComponent.h>
#include <LightSystem/LogicalLayer/LESpotLightComponent.h>

ULightEntityHelper::ULightEntityHelper()
{

}

ULightEntityHelper* ULightEntityHelper::Instance = nullptr;

ULightEntityHelper* ULightEntityHelper::GetInstance()
{
	if (Instance == nullptr) {
		Instance = NewObject<ULightEntityHelper>();
	}
	return Instance;
}


FString ULightEntityHelper::GetTabStr(const int num)
{
	FString ans = "";
	for (int i = 0; i < num; ++i) {
		ans += "\t";
	}
	return ans;
}

void ULightEntityHelper::StrStrParsor(const FString& str, FString& key, FString& value)
{
	int index;
	if (str.FindChar(':', index)) {
		key = str.Left(index);
		key.TrimStartAndEndInline();
		value = str.Right(str.Len() - index - 1);
		value.TrimStartAndEndInline();
	}
	else {
		key = FString(str).TrimStartAndEnd();
	}
}

FString ULightEntityHelper::StrStrUnParsor(FString key, FString value, int tabNum)
{
	return GetTabStr(tabNum) + key + " : " + value;
}

USceneComponent* ULightEntityHelper::CreateSubobject(UObject* obj, FString ClassType)
{
	if (ClassType == ULEStaticMeshComponent::StaticClass()->GetName()) {
		return NewObject<ULEStaticMeshComponent>(obj, "StaticMeshComp");
	}
	else if (ClassType == ULEDirectionalLightComponent::StaticClass()->GetName()) {
		return NewObject<ULEDirectionalLightComponent>(obj, "DirectionalLightComp");
	}
	else if (ClassType == ULEPointLightComponent::StaticClass()->GetName()) {
		return NewObject<ULEPointLightComponent>(obj, "PointLightComp");
	}
	else if (ClassType == ULERectLightComponent::StaticClass()->GetName()) {
		return NewObject<ULERectLightComponent>(obj, "RectLightComp");
	}
	else if (ClassType == ULESpotLightComponent::StaticClass()->GetName()) {
		return NewObject<ULESpotLightComponent>(obj, "SpotLightComp");
	}
	return nullptr;
}

bool ULightEntityHelper::LoadDataFromJsonFile(ALightEntity* LEData, FString FileName)
{
	if (LEData == nullptr) {
		return false;
	}
	FileName = UGamePathToolFunctionLibrary::GetGameLightEntityJSONDir() + FileName;
	IFileManager& FileManager = IFileManager::Get();
	if (FileManager.FileExists(*FileName)) {
		ISaveAndLoadJsonData* ISLData = Cast<ISaveAndLoadJsonData>(LEData->GetRootComponent());
		if (ISLData) {
			TArray<FString> dataStrList;
			if (FFileHelper::LoadFileToStringArray(dataStrList, *FileName)) {
				int deepth = 0;
				ISLData->SetDataFromJson(dataStrList, deepth);
				return true;
			}
		}
		return false;
	}
	return false;
}

bool ULightEntityHelper::SaveDataToJsonFile(ALightEntity* LEData, FString FileName)
{
	if (LEData == nullptr) {
		return false;
	}
	FileName = UGamePathToolFunctionLibrary::GetGameLightEntityJSONDir() + FileName;
	FText errorText;
	IFileManager& FileManager = IFileManager::Get();
	if (!FileManager.DirectoryExists(*UGamePathToolFunctionLibrary::GetGameLightEntityJSONDir())) {
		FileManager.MakeDirectory(*UGamePathToolFunctionLibrary::GetGameLightEntityJSONDir());
	}
	if (FFileHelper::IsFilenameValidForSaving(FileName, errorText)) {
		ISaveAndLoadJsonData* ISLData = Cast<ISaveAndLoadJsonData>(LEData->GetRootComponent());
		if (ISLData) {
			TArray<FString> dataStrList = ISLData->GetDataAsJson(0);
			return FFileHelper::SaveStringArrayToFile(dataStrList, *FileName, FFileHelper::EEncodingOptions::ForceUTF8);
		}
		return false;
	}
	return false;
}
