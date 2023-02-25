// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightEntity.generated.h"

class ULEStaticMeshComponent;

// 所有 AttachedComponents 都必须在RootComponent下，可以有多级

UCLASS()
class LIGHTINGSIMULATOR_API ALightEntity : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	ULEStaticMeshComponent* rootComp;
	
public:	
	// Sets default values for this actor's properties
	ALightEntity();

	/// <summary>
	/// 将 此类的 Component 数据存入 JSON 文件
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "SaveAndLoad")
	bool SaveCompDataToFile(FString FileName);

	/// <summary>
	/// 从 JSON 文件中读取数据并初始化此类
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "SaveAndLoad")
	bool LoadCompDataFromFile(FString FileName);

	/// <summary>
	/// 将 AttachComp 绑定到 OwnComp
	/// OwnComp 必须是此Entity (AActor) 已经 AttachComponents
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "Components")
	bool AttachComponent(USceneComponent* AttachComp, USceneComponent* OwnComp);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LightEntity|ClassTools")
	USceneComponent* CreateSubobject(FString ClassType);
};
