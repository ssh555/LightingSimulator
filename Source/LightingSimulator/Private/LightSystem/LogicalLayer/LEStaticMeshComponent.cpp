// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSystem/LogicalLayer/LEStaticMeshComponent.h"
#include "LightSystem/LogicalLayer/LightEntityHelper.h"
#include <UObject/UObjectGlobals.h>
#include <Internationalization/StringTable.h>
#include "Tools/StringTableToolFunctionLibrary.h"
#include <Kismet/KismetStringTableLibrary.h>


FString ULEStaticMeshComponent::GetData(const FString& key)
{
	if (key == "ClassType") {
		return this->GetClass()->GetName();
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
		return this->GetStaticMesh()->GetPathName();
	}
	return "";
}


void ULEStaticMeshComponent::SetData(FString& key, FString& value)
{
	if (key == "TransformLocation") {
		FVector vector;
		vector.InitFromString(value);
		this->SetRelativeLocation(vector);
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
		}
	}
}

