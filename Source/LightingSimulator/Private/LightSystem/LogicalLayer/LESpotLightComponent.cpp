// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSystem/LogicalLayer/LESpotLightComponent.h"
#include "LightSystem/LogicalLayer/LightEntityHelper.h"
#include "Tools/StringTableToolFunctionLibrary.h"
#include <Kismet/KismetStringTableLibrary.h>
#include <Internationalization/StringTable.h>


#include "LightSystem/LogicalLayer/LEOpFile.h"
#include "LightSystem/LogicalLayer/LETimeline.h"
#include <Kismet/KismetMaterialLibrary.h>


ULESpotLightComponent::ULESpotLightComponent()
{
	this->PrimaryComponentTick.bCanEverTick = true;
}

FString ULESpotLightComponent::GetData(const FString& key)
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
	else if (key == "InnerConeAngle") {
		return FString::SanitizeFloat(this->InnerConeAngle);
	}
	else if (key == "OuterConeAngle") {
		return FString::SanitizeFloat(this->OuterConeAngle);
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
	else if (key == "Rotation_Pitch") {
		return FString::SanitizeFloat(this->GetRelativeRotation().Pitch);
	}
	else if (key == "Rotation_Roll") {
		return FString::SanitizeFloat(this->GetRelativeRotation().Roll);
	}
	else if (key == "Rotation_Yaw") {
		return FString::SanitizeFloat(this->GetRelativeRotation().Yaw);
	}
	else if (key == "Scale_X") {
		return FString::SanitizeFloat(this->GetRelativeScale3D().X);
	}
	else if (key == "Scale_Y") {
		return FString::SanitizeFloat(this->GetRelativeScale3D().Y);
	}
	else if (key == "Scale_Z") {
		return FString::SanitizeFloat(this->GetRelativeScale3D().Z);
	}
	return "";
}

void ULESpotLightComponent::SetData(const FString& key, const FString& value)
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
	else if (key == "InnerConeAngle") {
		this->SetInnerConeAngle(FCString::Atof(*value));
	}
	else if (key == "OuterConeAngle") {
		this->SetOuterConeAngle(FCString::Atof(*value));
	}
	else if (key == "SourceRadius") {
		this->SetSourceRadius(FCString::Atof(*value));
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


void ULESpotLightComponent::BeginPlay()
{
	Super::BeginPlay();
	this->InitFile();

}

void ULESpotLightComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	this->Update(DeltaTime, TickType, ThisTickFunction);
}



