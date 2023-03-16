// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LightStudioGameMode.generated.h"

class ALightEntity;

/**
 * 
 */
UCLASS()
class LIGHTINGSIMULATOR_API ALightStudioGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	static bool bIsStart;

	static bool bIsPause;

	static void PrintString(FString str);

	static UObject* instance;

public:
	UPROPERTY(BlueprintReadOnly)
	TArray<FString> PrimitiveLightEntityList;

	/// <summary>
	/// <key, value> => <name, path>
	/// </summary>
	UPROPERTY(BlueprintReadOnly)
	TMap<FString, FString> StaticMeshMap;

	UPROPERTY(BlueprintReadOnly)
	TMap<FString, FString> MaterialMap;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsStart() {
		return this->bIsStart;
	}
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsPause() {
		return this->bIsPause;
	}

	UFUNCTION(BlueprintCallable)
	bool SetIsStart(bool isStart) {
		this->bIsStart = isStart;
		return this->bIsStart;
	}
	UFUNCTION(BlueprintCallable)
	bool SetIsPause(bool isPause) {
		this->bIsPause = isPause;
		return this->bIsPause;
	}



public:
	ALightStudioGameMode();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

};
