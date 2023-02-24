// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSystem/LogicalLayer/LESpotLightComponent.h"
#include "LightSystem/LogicalLayer/LightEntityHelper.h"

TArray<FString> ULESpotLightComponent::GetDataAsJson(const int deepth)
{
	TArray<FString> ans;

	FString tabStr = ULightEntityHelper::GetTabStr(deepth);
	ans.Add(tabStr + "[");

	const int Deepth = deepth + 1;

	ans.Add(ULightEntityHelper::StrStrUnParsor("ClassType", this->GetClass()->GetName(), Deepth));
	ans.Add(ULightEntityHelper::StrStrUnParsor("TransformLocation", this->GetRelativeLocation().ToString(), Deepth));
	ans.Add(ULightEntityHelper::StrStrUnParsor("TransformRotation", this->GetRelativeRotation().ToString(), Deepth));
	ans.Add(ULightEntityHelper::StrStrUnParsor("TransformScale", this->GetRelativeScale3D().ToString(), Deepth));
	ans.Add(ULightEntityHelper::StrStrUnParsor("Intensity", FString::SanitizeFloat(this->Intensity), Deepth));
	ans.Add(ULightEntityHelper::StrStrUnParsor("LightColor", this->LightColor.ToString(), Deepth));
	ans.Add(ULightEntityHelper::StrStrUnParsor("AttenuationRadius", FString::SanitizeFloat(this->AttenuationRadius), Deepth));
	ans.Add(ULightEntityHelper::StrStrUnParsor("InnerConeAngle", FString::SanitizeFloat(this->InnerConeAngle), Deepth));
	ans.Add(ULightEntityHelper::StrStrUnParsor("OuterConeAngle", FString::SanitizeFloat(this->OuterConeAngle), Deepth));
	ans.Add(ULightEntityHelper::StrStrUnParsor("SoftSourceRadius", FString::SanitizeFloat(this->SoftSourceRadius), Deepth));
	ans.Add(ULightEntityHelper::StrStrUnParsor("SourceLength", FString::SanitizeFloat(this->SourceLength), Deepth));
	ans.Add(ULightEntityHelper::StrStrUnParsor("Temperature", FString::SanitizeFloat(this->Temperature), Deepth));
	ans.Add(ULightEntityHelper::StrStrUnParsor("UseTemperature", this->bUseTemperature ? TEXT("true") : TEXT("false"), Deepth));
	ans.Add(ULightEntityHelper::StrStrUnParsor("AffectsWorld", this->bAffectsWorld ? TEXT("true") : TEXT("false"), Deepth));
	ans.Add(ULightEntityHelper::StrStrUnParsor("CastShadows", this->CastShadows ? TEXT("true") : TEXT("false"), Deepth));
	ans.Add(ULightEntityHelper::StrStrUnParsor("IndirectLightingIntensity", FString::SanitizeFloat(this->IndirectLightingIntensity), Deepth));
	ans.Add(ULightEntityHelper::StrStrUnParsor("VolumetricScatteringIntensity", FString::SanitizeFloat(this->VolumetricScatteringIntensity), Deepth));




	for (USceneComponent* child : this->GetAttachChildren())
	{
		ISaveAndLoadJsonData* ISLData = Cast<ISaveAndLoadJsonData>(child);
		if (ISLData) {
			ans.Append(ISLData->GetDataAsJson(Deepth));
		}
	}

	ans.Add(tabStr + "]");
	return ans;
}

void ULESpotLightComponent::SetDataFromJson(TArray<FString> dataStrList, int& deepth)
{
	int stackNum = 0;
	FString key, value;
	ULightEntityHelper::StrStrParsor(dataStrList[deepth++], key, value);
	// ��ǰ�������� [�����Լ����������]
	if (ensureAlways(key == "[")) {
		++stackNum;
		// ������ ClassType �ܶ�Ӧ
		ULightEntityHelper::StrStrParsor(dataStrList[deepth++], key, value);
		if (ensureAlways(key == "ClassType" && value == this->GetClass()->GetName())) {
			for (; deepth < dataStrList.Num(); ) {
				ULightEntityHelper::StrStrParsor(dataStrList[deepth++], key, value);
				// ����� [ => ���������
				if (key == "[") {
					ULightEntityHelper::StrStrParsor(dataStrList[deepth], key, value);
					// ������ ������� ClassType �ܶ�Ӧ
					if (ensureAlways(key == "ClassType")) {
						USceneComponent* childComp = ULightEntityHelper::CreateSubobject(this->GetOwner(), value);
						// ���������
						if (ensureAlways(childComp)) {
							//��Ҫ�������޷���ϸ������п������
							this->GetOwner()->AddInstanceComponent(childComp);
							//��Ҫ������Ҫע�����
							childComp->RegisterComponent();
							childComp->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
							Cast<ISaveAndLoadJsonData>(childComp)->SetDataFromJson(dataStrList, --deepth);
							++stackNum;
						}
					}
				}
				// ����� ] => �ж��Ƿ�Ϊ��ǰ����� ] 
				else if (key == "]") {
					// ������ǰ����� ]
					if (--stackNum == 0) {
						return;
					}
				}
				// ������ǰ���������
				else {
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
						this->Intensity = FCString::Atof(*value);
					}
					else if (key == "LightColor") {
						FColor color;
						color.InitFromString(value);
						this->LightColor = color;
					}
					else if (key == "AttenuationRadius") {
						this->AttenuationRadius = FCString::Atof(*value);
					}
					else if (key == " InnerConeAngle") {
						this->InnerConeAngle = FCString::Atof(*value);
					}
					else if (key == " InnerConeAngle") {
						this->OuterConeAngle = FCString::Atof(*value);
					}
					else if (key == " SoftSourceRadius") {
						this->SoftSourceRadius = FCString::Atof(*value);
					}
					else if (key == " SourceLength") {
						this->SourceLength = FCString::Atof(*value);
					}
					else if (key == " Temperature") {
						this->Temperature = FCString::Atof(*value);
					}
					else if (key == "UseTemperature") {
						this->bUseTemperature = value.ToBool();
					}
					else if (key == "AffectsWorld") {
						this->bAffectsWorld = value.ToBool();
					}
					else if (key == "CastShadows") {
						this->CastShadows = value.ToBool();
					}
					else if (key == " IndirectLightingIntensity") {
						this->IndirectLightingIntensity = FCString::Atof(*value);
					}
					else if (key == " VolumericScatteringIntensity") {
						this->VolumetricScatteringIntensity = FCString::Atof(*value);
					}
				}
			}
		}
	}
}
