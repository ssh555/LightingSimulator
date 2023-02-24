// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSystem/LogicalLayer/LEStaticMeshComponent.h"
#include "LightSystem/LogicalLayer/LightEntityHelper.h"

TArray<FString> ULEStaticMeshComponent::GetDataAsJson(const int deepth)
{
	TArray<FString> ans;

	FString tabStr = ULightEntityHelper::GetTabStr(deepth);

	const int Deepth = deepth + 1;

	ans.Add(tabStr + "[");
	ans.Add(ULightEntityHelper::StrStrUnParsor("ClassType", this->GetClass()->GetName(), Deepth));
	ans.Add(ULightEntityHelper::StrStrUnParsor("TransformLocation", this->GetRelativeLocation().ToString(), Deepth));
	ans.Add(ULightEntityHelper::StrStrUnParsor("TransformRotation", this->GetRelativeRotation().ToString(), Deepth));
	ans.Add(ULightEntityHelper::StrStrUnParsor("TransformScale", this->GetRelativeScale3D().ToString(), Deepth));

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

void ULEStaticMeshComponent::SetDataFromJson(TArray<FString> dataStrList, int& deepth)
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
				}
			}
		}
	}
}
