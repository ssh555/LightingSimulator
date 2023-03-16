// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSystem/LogicalLayer/LEStaticMeshComponent.h"
#include "LightSystem/LogicalLayer/LightEntityHelper.h"
#include <UObject/UObjectGlobals.h>
#include <Internationalization/StringTable.h>
#include "Tools/StringTableToolFunctionLibrary.h"
#include <Kismet/KismetStringTableLibrary.h>
#include <Kismet/KismetSystemLibrary.h>
#include "LightSystem/LogicalLayer/LEOpFile.h"
#include "LightSystem/LogicalLayer/LETimeline.h"
#include <Materials/MaterialInstance.h>
#include "LightSystem/LightStudioGameMode.h"
#include <Materials/MaterialInterface.h>


ULEStaticMeshComponent::ULEStaticMeshComponent()
{
	this->PrimaryComponentTick.bCanEverTick = true;
}

FString ULEStaticMeshComponent::GetData(const FString& key)
{
	if (key == "ClassType") 
	{
		return this->GetClass()->GetName();
	}
	else if (key == "Name") {
		FString ans;
		this->GetName(ans);
		return ans;
	}
	else if (key == "TransformLocation") {
		return this->GetRelativeLocation().ToString();
	}
	else if (key == "TransformRotation") {
		return this->GetRelativeRotation().ToString();
	}
	else if (key == "TransformScale") {
		return this->GetRelativeScale3D().ToString();
	}
	else if (key == "StaticMeshPath") {
		if (!this->GetStaticMesh())
		{
			return "None";
		}
		return this->GetStaticMesh()->GetPathName();
	}
	else if (key == "StaticMeshName") {
		if (!this->GetStaticMesh())
		{
			return "None";
		}
		return this->GetStaticMesh()->GetName();
	}
	else if (key == "LEOpFile") {
		return this->TickFile->FileName;
	}
	else if (key == "LETimeline") {
		return this->TimeFile->FileName;
	}
	else if (key == "MaterialPath") {
		if (!this->GetMaterial(0)) {
			return "None";
		}
		return this->MatPath;
	}
	return "";
}


void ULEStaticMeshComponent::SetData(const FString& key, const FString& value)
{
	if (key == "TransformLocation") {
		FVector vector;
		vector.InitFromString(value);
		this->SetRelativeLocation(vector);
	}
	else if (key == "Name") {
		this->Rename(*value);
	}
	else if (key == "TransformRotation") {
		FRotator rot;
		rot.InitFromString(value);
		this->SetRelativeRotation(rot);
	}
	else if (key == "TransformScale") {
		FVector vector;
		vector.InitFromString(value);
		this->SetRelativeScale3D(vector);
	}
	else if (key == "StaticMeshPath") {
		if (value != " None") {
			this->SetStaticMesh(LoadObject<UStaticMesh>(this, *value));
			//this->MatPath = this->GetMaterial(0)->GetPathName();
		}
	}
	else if (key == "LEOpFile") {
		this->TickFile->SetFile(value, this);
	}
	else if (key == "LETimeline") {
		this->TimeFile->SetFile(value, this);
	}
	else if (key == "MaterialPath") {
		if (value != "None") {
			this->MatPath = value;
			this->MatInst = CreateDynamicMaterialInstance(0, LoadObject<UMaterialInterface>(this, *value));
		}
	}
}

void ULEStaticMeshComponent::BeginPlay()
{
	Super::BeginPlay();
	this->InitFile();
}

void ULEStaticMeshComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	this->Update(DeltaTime, TickType, ThisTickFunction);
}

