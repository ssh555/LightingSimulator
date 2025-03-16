// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightEntity.generated.h"

class ULEStaticMeshComponent;

// ���� AttachedComponents ��������RootComponent�£������ж༶

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
	/// �� ����� Component ���ݴ����ļ�
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "LightEntity|SaveAndLoad")
	bool SaveCompDataToFile(FString FileName);

	/// <summary>
	/// ���ļ��ж�ȡ���ݲ���ʼ������
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "LightEntity|SaveAndLoad")
	bool LoadCompDataFromFile(FString FileName);

	/// <summary>
	/// �� AttachComp �󶨵� OwnComp
	/// OwnComp �����Ǵ�Entity (AActor) �Ѿ� AttachComponents
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "LightEntity|Components")
	bool AttachComponent(USceneComponent* AttachComp, USceneComponent* OwnComp);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LightEntity|ClassTools")
	USceneComponent* CreateSubobject(FString ClassType);

	UFUNCTION(BlueprintCallable, Category = "LightEntity|Components")
	void DestroyAllChildren();

	UFUNCTION(BlueprintCallable, Category = "LightEntity|Components")
	void DestroyLEComponent(USceneComponent* Comp);

	UFUNCTION(BlueprintCallable, Category = "LightEntity|Components")
	bool RenameComp(USceneComponent* Comp, FString newName);

	UFUNCTION(BlueprintCallable, Category = "LightEntity|Components")
	bool AddLEToComp(USceneComponent* OwnComp, FString LEFilePath);
};
