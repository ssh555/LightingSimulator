// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSystem/LightStudioGameMode.h"
#include <GameFramework/GameModeBase.h>
#include <LightSystem/PresentationLayer/LSCameraPawn.h>
#include <Kismet/GameplayStatics.h>
#include <LightSystem/LogicalLayer/LightEntity.h>
#include <EngineUtils.h>
#include <Engine/StaticMesh.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Materials/Material.h>
#include <Misc/FileHelper.h>
#include <Tools/GamePathToolFunctionLibrary.h>

bool ALightStudioGameMode::bIsStart = false;

bool ALightStudioGameMode::bIsPause = false;

UObject* ALightStudioGameMode::instance = nullptr;

void ALightStudioGameMode::PrintString(FString str)
{
	UKismetSystemLibrary::PrintString(ALightStudioGameMode::instance, str);
}


ALightStudioGameMode::ALightStudioGameMode()
{
	this->DefaultPawnClass = ALSCameraPawn::StaticClass();
	ALightStudioGameMode::instance = this;

	ALightStudioGameMode::bIsStart = false;

	ALightStudioGameMode::bIsPause = false;
	//UGameplayStatics::SetViewportMouseCaptureMode(this, EMouseCaptureMode::NoCapture);
}

void ALightStudioGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	this->StaticMeshMap.Add("None", "None");

	TArray<UObject*> LoadedAsseObjects;
	FString ResourcePath(TEXT("/Game/LightingSimulator/Meshes"));

	TArray<FString> dataStrList;

	if (EngineUtils::FindOrLoadAssetsByPath(ResourcePath, LoadedAsseObjects, EngineUtils::ATL_Regular))//寻找到所有的资源
	{
		for (UObject* TmpAssetObject : LoadedAsseObjects)
		{
			if (UStaticMesh* mesh = Cast<UStaticMesh>(TmpAssetObject)) {
				this->StaticMeshMap.Add(mesh->GetName(), mesh->GetPathName());
				dataStrList.Add("StaticMesh " + mesh->GetName() + " : " + mesh->GetPathName());
			}
			else if (UMaterial* mat = Cast<UMaterial>(TmpAssetObject)) {
				//PrintString(mat->GetName() + "   " + mat->GetPathName());
				this->MaterialMap.Add(mat->GetName(), mat->GetPathName());
				dataStrList.Add("Material " + mat->GetName() + " : " + mat->GetPathName());
			}
			else if (UTexture2D* tex2d = Cast<UTexture2D>(TmpAssetObject)) {
				dataStrList.Add("Texture2D " + tex2d->GetName() + " : " + tex2d->GetPathName());
			}
		}
	}
	dataStrList.Sort();
	FString filePath;
	filePath = UGamePathToolFunctionLibrary::GetGameContentDir() + "Resources.data";
	FFileHelper::SaveStringArrayToFile(dataStrList, *filePath, FFileHelper::EEncodingOptions::ForceUTF8);
	//ResourcePath = "/Engine/BasicShapes";
	//if (EngineUtils::FindOrLoadAssetsByPath(ResourcePath, LoadedAsseObjects, EngineUtils::ATL_Regular))//寻找到所有的资源
	//{
	//	for (UObject* TmpAssetObject : LoadedAsseObjects)
	//	{
	//		UStaticMesh* mesh = Cast<UStaticMesh>(TmpAssetObject);
	//		if (mesh) {
	//			this->StaticMeshMap.Add(mesh->GetName(), mesh->GetPathName());
	//		}
	//	}

	//}
}
