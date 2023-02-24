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
				}
			}
		}
	}
}
