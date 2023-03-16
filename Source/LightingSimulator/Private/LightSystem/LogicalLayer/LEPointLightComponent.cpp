// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSystem/LogicalLayer/LEPointLightComponent.h"
#include "LightSystem/LogicalLayer/LightEntityHelper.h"
#include <Kismet/KismetStringTableLibrary.h>
#include "Tools/StringTableToolFunctionLibrary.h"
#include <Internationalization/StringTable.h>
#include "LightSystem/LogicalLayer/LEOpFile.h"
#include "LightSystem/LogicalLayer/LETimeline.h"
#include <Kismet/KismetMaterialLibrary.h>



ULEPointLightComponent::ULEPointLightComponent()
{
	this->PrimaryComponentTick.bCanEverTick = true;

}

FString ULEPointLightComponent::GetData(const FString& key)
{
	if (key == "ClassType") {
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
	else if (key == "Intensity") {
		return FString::SanitizeFloat(this->Intensity);
	}
	else if (key == "LightColor") {
		return this->LightColor.ToString();
	}
	else if (key == "AttenuationRadius") {
		return FString::SanitizeFloat(this->AttenuationRadius);
	}
	else if (key == "SourceRadius") {
		return FString::SanitizeFloat(this->SourceRadius);
	}
	else if (key == "SoftSourceRadius") {
		return FString::SanitizeFloat(this->SoftSourceRadius);
	}
	else if (key == "SourceLength") {
		return FString::SanitizeFloat(this->SourceLength);
	}
	else if (key == "Temperature") {
		return FString::SanitizeFloat(this->Temperature);
	}
	else if (key == "UseTemperature") {
		return this->bUseTemperature ? TEXT("true") : TEXT("false");
	}
	else if (key == "AffectsWorld") {
		return this->bAffectsWorld ? TEXT("true") : TEXT("false");
	}
	else if (key == "CastShadows") {
		return this->CastShadows ? TEXT("true") : TEXT("false");
	}
	else if (key == "IndirectLightingIntensity") {
		return FString::SanitizeFloat(this->IndirectLightingIntensity);
	}
	else if (key == "VolumericScatteringIntensity") {
		return FString::SanitizeFloat(this->VolumetricScatteringIntensity);
	}
	else if (key == "LEOpFile") {
		return this->TickFile->FileName;
	}
	else if (key == "LETimeline") {
		return this->TimeFile->FileName;
	}
	else if (key == "LightFunctionMaterialPath") {
		if (!this->LightFunctionMaterial) {
			return "None";
		}
		return this->MatPath;
	}
	return "";
}


void ULEPointLightComponent::SetData(const FString& key, const FString& value)
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
	else if (key == "Intensity") {
		this->SetIntensity(FCString::Atof(*value));
	}
	else if (key == "LightColor") {
		FColor color;
		color.InitFromString(value);
		this->SetLightColor(color);
	}
	else if (key == "AttenuationRadius") {
		this->SetAttenuationRadius(FCString::Atof(*value));
	}
	else if (key == "SourceRadius") {
		this->SourceRadius = FCString::Atof(*value);
	}
	else if (key == "SoftSourceRadius") {
		this->SetSoftSourceRadius(FCString::Atof(*value));
	}
	else if (key == "SourceLength") {
		this->SetSourceLength(FCString::Atof(*value));
	}
	else if (key == "Temperature") {
		this->SetTemperature(FCString::Atof(*value));
	}
	else if (key == "UseTemperature") {
		this->SetUseTemperature(value.ToBool());
	}
	else if (key == "AffectsWorld") {
		this->bAffectsWorld = value.ToBool();
	}
	else if (key == "CastShadows") {
		this->SetCastShadows(value.ToBool());
	}
	else if (key == "IndirectLightingIntensity") {
		this->SetIndirectLightingIntensity(FCString::Atof(*value));
	}
	else if (key == "VolumericScatteringIntensity") {
		this->SetVolumetricScatteringIntensity(FCString::Atof(*value));
	}
	else if (key == "LEOpFile") {
		this->TickFile->SetFile(value, this);
	}
	else if (key == "LETimeline") {
		this->TimeFile->SetFile(value, this);
	}
	else if (key == "LightFunctionMaterialPath") {
		if (value != "None") {
			this->MatPath = value;
			this->MatInst = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, LoadObject<UMaterialInterface>(this, *value));
			this->SetLightFunctionMaterial(this->MatInst);
		}
	}
}

void ULEPointLightComponent::BeginPlay()
{
	Super::BeginPlay();
	this->InitFile();

}

void ULEPointLightComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	this->Update(DeltaTime, TickType, ThisTickFunction);
}

