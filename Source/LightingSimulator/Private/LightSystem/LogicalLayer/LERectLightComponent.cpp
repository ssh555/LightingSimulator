// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSystem/LogicalLayer/LERectLightComponent.h"
#include "LightSystem/LogicalLayer/LightEntityHelper.h"
#include <Kismet/KismetStringTableLibrary.h>
#include "Tools/StringTableToolFunctionLibrary.h"
#include <Internationalization/StringTable.h>





FString ULERectLightComponent::GetData(const FString& key)
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
	else if (key == "Intensity") {
		return FString::SanitizeFloat(this->Intensity);
	}
	else if (key == "LightColor") {
		return this->LightColor.ToString();
	}
	else if (key == "AttenuationRadius") {
		return FString::SanitizeFloat(this->AttenuationRadius);
	}
	else if (key == "SourceWidth") {
		return FString::SanitizeFloat(this->SourceWidth);
	}
	else if (key == "SourceHeight") {
		return FString::SanitizeFloat(this->SourceHeight);
	}
	else if (key == "BarnDoorAngle") {
		return FString::SanitizeFloat(this->BarnDoorAngle);
	}
	else if (key == "BarnDoorLength") {
		return FString::SanitizeFloat(this->BarnDoorLength);
	}
	// [SourceTexture : Texture] [����]
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
	return "";
}
//
//TArray<FString> ULERectLightComponent::GetAllDatas(const int deepth)
//{
//	TArray<FString> ans;
//
//	TArray<FString> keys = UKismetStringTableLibrary::GetKeysFromStringTable(this->StrTable->GetStringTableId());
//	for (FString key : keys)
//	{
//		ans.Add(ULightEntityHelper::StrStrUnParsor(key, this->GetData(key), deepth));
//	}
//
//
//	return ans;
//}

void ULERectLightComponent::SetData(FString& key, FString& value)
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
	else if (key == "SourceWidth") {
		this->SetSourceWidth(FCString::Atof(*value));
	}
	else if (key == "SourceHeight") {
		this->SetSourceHeight(FCString::Atof(*value));
	}
	else if (key == "BarnDoorAngle") {
		this->SetBarnDoorAngle(FCString::Atof(*value));
	}
	else if (key == "BarnDoorLength") {
		this->SetBarnDoorLength(FCString::Atof(*value));
	}
	// [SourceTexture : Texture] [����]
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
}



