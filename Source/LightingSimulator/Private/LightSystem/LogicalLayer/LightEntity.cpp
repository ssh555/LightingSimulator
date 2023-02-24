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

// Sets default values
ALightEntity::ALightEntity()
{
	////NewObject时一定要传入outer*，否则在编辑器中无法显示
	//StaticMeshComponent = NewObject<UStaticMeshComponent>(this, TEXT("StaticMeshComponent"));
	////重要，否则无法在细节面板中看到组件
	//this->AddInstanceComponent(StaticMeshComponent);
	////重要，必须要注册组件
	//StaticMeshComponent->RegisterComponent();
	////组件绑定，与构造函数中调用的不同
	//this->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	this->rootComp = CreateDefaultSubobject<ULEStaticMeshComponent>("RootComp");
	this->SetRootComponent(rootComp);

	ULEDirectionalLightComponent* DirectionalLightComp = CreateDefaultSubobject<ULEDirectionalLightComponent>("DirectionalLightComp");
	DirectionalLightComp->SetupAttachment(this->RootComponent);

	ULEPointLightComponent* PointLightComp = CreateDefaultSubobject<ULEPointLightComponent>("PointLightComp");
	PointLightComp->SetupAttachment(DirectionalLightComp);

	ULERectLightComponent* RectLightComp = CreateDefaultSubobject<ULERectLightComponent>("RectLightComp");
	RectLightComp->SetupAttachment(this->RootComponent);

	ULESpotLightComponent* SpotLightComp = CreateDefaultSubobject<ULESpotLightComponent>("SpotLightComp");
	SpotLightComp->SetupAttachment(PointLightComp);

	// Runtime 使用 AttachToComponent
}

ALightEntity::ALightEntity(FString FileName)
{
	this->LoadCompDataFromJSONFile(FileName);
}

bool ALightEntity::SaveCompDataToJSONFile(FString FileName)
{
	ULightEntityHelper* helper = ULightEntityHelper::GetInstance();
	return helper->SaveDataToJsonFile(this, FileName);
}

bool ALightEntity::LoadCompDataFromJSONFile(FString FileName)
{
	ULightEntityHelper* helper = ULightEntityHelper::GetInstance();
	return helper->LoadDataFromJsonFile(this, FileName);
}

