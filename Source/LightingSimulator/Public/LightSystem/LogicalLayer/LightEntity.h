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
	/// �� ����� Component ���ݴ��� JSON �ļ�
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "SaveAndLoad")
	bool SaveCompDataToJSONFile(FString FileName);

	/// <summary>
	/// �� JSON �ļ��ж�ȡ���ݲ���ʼ������
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "SaveAndLoad")
	bool LoadCompDataFromJSONFile(FString FileName);


};
