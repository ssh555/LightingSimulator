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
	// 当前解析的是 [属于自己组件的数据]
	if (ensureAlways(key == "[")) {
		++stackNum;
		// 解析的 ClassType 能对应
		ULightEntityHelper::StrStrParsor(dataStrList[deepth++], key, value);
		if (ensureAlways(key == "ClassType" && value == this->GetClass()->GetName())) {
			for (; deepth < dataStrList.Num(); ) {
				ULightEntityHelper::StrStrParsor(dataStrList[deepth++], key, value);
				// 如果是 [ => 进入子组件
				if (key == "[") {
					ULightEntityHelper::StrStrParsor(dataStrList[deepth], key, value);
					// 解析的 子组件的 ClassType 能对应
					if (ensureAlways(key == "ClassType")) {
						USceneComponent* childComp = ULightEntityHelper::CreateSubobject(this->GetOwner(), value);
						// 子组件存在
						if (ensureAlways(childComp)) {
							//重要，否则无法在细节面板中看到组件
							this->GetOwner()->AddInstanceComponent(childComp);
							//重要，必须要注册组件
							childComp->RegisterComponent();
							childComp->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
							Cast<ISaveAndLoadJsonData>(childComp)->SetDataFromJson(dataStrList, --deepth);
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
