// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSystem/LogicalLayer/LightEntityHelper.h"
#include "Tools/GamePathToolFunctionLibrary.h"
#include "LightSystem/LogicalLayer/SaveAndLoadData.h"
#include "LightSystem/LogicalLayer/LightEntity.h"
#include <HAL/FileManager.h>
#include <Misc/FileHelper.h>
#include "LightSystem/LogicalLayer/LEDirectionalLightComponent.h"
#include <UObject/Object.h>
#include "LightSystem/LogicalLayer/LEStaticMeshComponent.h"
#include <LightSystem/LogicalLayer/LEPointLightComponent.h>
#include <LightSystem/LogicalLayer/LERectLightComponent.h>
#include <LightSystem/LogicalLayer/LESpotLightComponent.h>
#include "LightSystem/LogicalLayer/SaveAndLoadData.h"

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

bool ULightEntityHelper::LoadDataFromFile(ALightEntity* LEData, FString FileName)
{
	if (LEData == nullptr) {
		return false;
	}
	if (!FileName.ToLower().Contains(".ledata")) {
		FileName += ".ledata";
	}
	FileName = UGamePathToolFunctionLibrary::GetGameLightEntityDataDir() + FileName;
	IFileManager& FileManager = IFileManager::Get();
	if (FileManager.FileExists(*FileName)) {
		ISaveAndLoadData* ISLData = Cast<ISaveAndLoadData>(LEData->GetRootComponent());
		if (ISLData) {
			TArray<FString> dataStrList;
			if (FFileHelper::LoadFileToStringArray(dataStrList, *FileName)) {
				int deepth = 0;
				LoadDataToISL(ISLData, dataStrList, deepth);
				return true;
			}
		}
		return false;
	}
	return false;
}

void ULightEntityHelper::LoadDataToISL(ISaveAndLoadData* ISLData, TArray<FString>& dataStrList, int& deepth)
{
	int stackNum = 0;
	FString key, value;
	ULightEntityHelper::StrStrParsor(dataStrList[deepth++], key, value);
	// 当前解析的是 [属于自己组件的数据]
	if (ensureAlways(key == "[")) {
		++stackNum;
		// 解析的 ClassType 能对应
		ULightEntityHelper::StrStrParsor(dataStrList[deepth++], key, value);
		USceneComponent* owner = Cast<USceneComponent>(ISLData);
		if (ensureAlways(key == "ClassType" && value == owner->GetClass()->GetName())) {
			for (; deepth < dataStrList.Num(); ) {
				ULightEntityHelper::StrStrParsor(dataStrList[deepth++], key, value);
				// 如果是 [ => 进入子组件
				if (key == "[") {
					ULightEntityHelper::StrStrParsor(dataStrList[deepth], key, value);
					// 解析的 子组件的 ClassType 能对应
					if (ensureAlways(key == "ClassType")) {
						USceneComponent* childComp = ULightEntityHelper::CreateSubobject(owner->GetOwner(), value);
						// 子组件存在
						if (ensureAlways(childComp)) {
							//重要，否则无法在细节面板中看到组件
							owner->GetOwner()->AddInstanceComponent(childComp);
							//重要，必须要注册组件
							childComp->RegisterComponent();
							childComp->AttachToComponent(Cast<USceneComponent>(ISLData), FAttachmentTransformRules::KeepRelativeTransform);
							LoadDataToISL(Cast<ISaveAndLoadData>(childComp), dataStrList, --deepth);
							++stackNum;
						}
					}
				}
				// 如果是 ] => 判断是否为当前组件的 ] 
				else if (key == "]") {
					// 遇到当前组件的 ]
					if (--stackNum == 0) {
						return;
					}
				}
				// 解析当前组件的数据
				else {
					ISLData->SetData(key, value);
				}
			}
		}
	}
}

bool ULightEntityHelper::SaveDataToFile(ALightEntity* LEData, FString FileName)
{
	if (LEData == nullptr) {
		return false;
	}
	if (!FileName.ToLower().Contains(".ledata")) {
		FileName += ".ledata";
	}
	FileName = UGamePathToolFunctionLibrary::GetGameLightEntityDataDir() + FileName;
	FText errorText;
	IFileManager& FileManager = IFileManager::Get();
	if (!FileManager.DirectoryExists(*UGamePathToolFunctionLibrary::GetGameLightEntityDataDir())) {
		FileManager.MakeDirectory(*UGamePathToolFunctionLibrary::GetGameLightEntityDataDir());
	}
	if (FFileHelper::IsFilenameValidForSaving(FileName, errorText)) {
		ISaveAndLoadData* ISLData = Cast<ISaveAndLoadData>(LEData->GetRootComponent());
		if (ISLData) {
			TArray<FString> dataStrList = SaveDataFromISL(ISLData, 0);
			return FFileHelper::SaveStringArrayToFile(dataStrList, *FileName, FFileHelper::EEncodingOptions::ForceUTF8);
		}
		return false;
	}
	return false;
}

TArray<FString> ULightEntityHelper::SaveDataFromISL(ISaveAndLoadData* ISLData,const int deepth)
{
	TArray<FString> ans;

	FString tabStr = ULightEntityHelper::GetTabStr(deepth);

	FString tabChildStr = ULightEntityHelper::GetTabStr(deepth + 1);

	ans.Add(tabStr + "[");

	ans.Append(ISLData->GetAllDatas(deepth + 1));

	for (USceneComponent* child : Cast<USceneComponent>(ISLData)->GetAttachChildren())
	{
		ISaveAndLoadData* ISLData = Cast<ISaveAndLoadData>(child);
		if (ISLData) {
			ans.Append(SaveDataFromISL(ISLData, deepth + 1));
		}
	}

	ans.Add(tabStr + "]");
	return ans;
}
