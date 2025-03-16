// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSystem/LogicalLayer/LightEntity.h"
#include "Tools/GamePathToolFunctionLibrary.h"
#include "LightSystem/LogicalLayer/LightEntityHelper.h"
#include "LightSystem/LogicalLayer/LEDirectionalLightComponent.h"
#include <Components/StaticMeshComponent.h>
#include <LightSystem/LogicalLayer/LEStaticMeshComponent.h>
#include "LightSystem/LogicalLayer/LEPointLightComponent.h"
#include "LightSystem/LogicalLayer/LERectLightComponent.h"
#include <LightSystem/LogicalLayer/LESpotLightComponent.h>
#include <Engine/World.h>

// Sets default values
ALightEntity::ALightEntity()
{
	////NewObjectʱһ��Ҫ����outer*�������ڱ༭�����޷���ʾ
	//StaticMeshComponent = NewObject<UStaticMeshComponent>(this, TEXT("StaticMeshComponent"));
	////��Ҫ�������޷���ϸ������п������
	//this->AddInstanceComponent(StaticMeshComponent);
	////��Ҫ������Ҫע�����
	//StaticMeshComponent->RegisterComponent();
	////����󶨣��빹�캯���е��õĲ�ͬ
	//this->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	this->rootComp = CreateDefaultSubobject<ULEStaticMeshComponent>("RootComp");
	this->SetRootComponent(rootComp);

	//ULEDirectionalLightComponent* DirectionalLightComp = CreateDefaultSubobject<ULEDirectionalLightComponent>("DirectionalLightComp");
	//DirectionalLightComp->SetupAttachment(this->RootComponent);

	//ULEPointLightComponent* PointLightComp = CreateDefaultSubobject<ULEPointLightComponent>("PointLightComp");
	//PointLightComp->SetupAttachment(rootComp);
	//PointLightComp = CreateDefaultSubobject<ULEPointLightComponent>("PointLightComp1");
	//PointLightComp->SetupAttachment(rootComp);

	//ULERectLightComponent* RectLightComp = CreateDefaultSubobject<ULERectLightComponent>("RectLightComp");
	//RectLightComp->SetupAttachment(this->RootComponent);

	//ULESpotLightComponent* SpotLightComp = CreateDefaultSubobject<ULESpotLightComponent>("SpotLightComp");
	//SpotLightComp->SetupAttachment(PointLightComp);
	// Runtime ʹ�� AttachToComponent
}

bool ALightEntity::SaveCompDataToFile(FString FileName)
{
	ULightEntityHelper* helper = ULightEntityHelper::GetInstance();
	return helper->SaveDataToFile(this, FileName);
}

bool ALightEntity::LoadCompDataFromFile(FString FileName)
{
	ULightEntityHelper* helper = ULightEntityHelper::GetInstance();
	return helper->LoadDataFromFile(this, FileName);
}

bool ALightEntity::AttachComponent(USceneComponent* AttachComp, USceneComponent* OwnComp)
{
	// �󶨶������������ ��Entity
	if (OwnComp->GetOwner() != this || AttachComp == nullptr) {
		return false;
	}
	if (AttachComp->AttachToComponent(OwnComp, FAttachmentTransformRules::KeepRelativeTransform)) {
		//UE_LOG(LogTemp, Log, TEXT("%d %d"), OwnComp->GetNumChildrenComponents(), rootComp->GetNumChildrenComponents());

		TArray<USceneComponent*> children;
		AttachComp->GetChildrenComponents(true, children);
		children.Add(AttachComp);
		for (USceneComponent* child : children) {

			//��Ҫ�������޷���ϸ������п������
			this->AddInstanceComponent(child);
			//��Ҫ������Ҫע�����
			child->RegisterComponent();
		}
		return true;
	}
	return false;
}

USceneComponent* ALightEntity::CreateSubobject(FString ClassType)
{
	return ULightEntityHelper::CreateSubobject(this, ClassType);
}

void ALightEntity::DestroyAllChildren()
{
	TArray<USceneComponent*> children;
	this->RootComponent->GetChildrenComponents(true, children);
	FString delName = "______deleta_______";
	for (USceneComponent* child : children)
	{
		child->Rename(*(child->GetName() + delName));
		child->DestroyComponent();
	}
}

void ALightEntity::DestroyLEComponent(USceneComponent* Comp)
{
	// ����ɾ�������
	if (Comp == this->rootComp) {
		return;
	}
	TArray<USceneComponent*> children;
	this->RootComponent->GetChildrenComponents(true, children);
	FString delName = "______deleta_______";
	for (USceneComponent* child : children)
	{
		if (child == Comp) {
			child->Rename(*(child->GetName() + delName));
			child->DestroyComponent();
			return;
		}
	}
}

bool ALightEntity::RenameComp(USceneComponent* Comp, FString newName)
{
	TArray<USceneComponent*> children;
	this->RootComponent->GetChildrenComponents(true, children);
	FString name;
	for (USceneComponent* child : children)
	{
		child->GetName(name);
		if (name == newName) {
			return false;
		}
	}
	Comp->Rename(*newName);
	return true;
}

bool ALightEntity::AddLEToComp(USceneComponent* OwnComp, FString LEFilePath)
{
	// �󶨶������������ ��Entity
	if (OwnComp->GetOwner() != this) {
		return false;
	}
	ALightEntity* LE = GetWorld()->SpawnActor<ALightEntity>(ALightEntity::StaticClass(), this->GetTransform());
	if (!LE->LoadCompDataFromFile(LEFilePath)) {
		return false;
	}
	TArray<USceneComponent*> LEchildren;
	LE->RootComponent->GetChildrenComponents(true, LEchildren);
	LEchildren.Add(LE->GetRootComponent());
	TArray<USceneComponent*> children;
	this->RootComponent->GetChildrenComponents(true, children);
	children.Add(this->GetRootComponent());
	bool flag = false;
	for (USceneComponent* LEchild : LEchildren) {
		do 
		{
			flag = false;
			for (USceneComponent* child : children) {
				if (child->GetName() == LEchild->GetName()) {
					LEchild->Rename(*(FString(LEchild->GetName() + "__rename__")));
					flag = true;
				}
			}
		} while (flag);

	}
	USceneComponent* comp = LE->rootComp;
	//LE->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	//LE->SetLifeSpan(2);
	return this->AttachComponent(comp, OwnComp);
}

