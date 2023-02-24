// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightEntity.generated.h"

class ULEStaticMeshComponent;

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

	ALightEntity(FString FileName);

	/// <summary>
	/// 将 此类的 Component 数据存入 JSON 文件
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "SaveAndLoad")
	bool SaveCompDataToJSONFile(FString FileName);

	/// <summary>
	/// 从 JSON 文件中读取数据并初始化此类
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "SaveAndLoad")
	bool LoadCompDataFromJSONFile(FString FileName);


};
