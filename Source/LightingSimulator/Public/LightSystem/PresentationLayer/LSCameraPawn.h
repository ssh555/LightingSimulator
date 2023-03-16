// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LEUserWidget.h"
#include <Templates/SubclassOf.h>
#include "Tools/MultiCastVoidAction.h"
#include "LSCameraPawn.generated.h"

class APlayerController;
class UCameraComponent;
class ULEUserWidget;

UCLASS()
class LIGHTINGSIMULATOR_API ALSCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALSCameraPawn();

protected:
	UPROPERTY(BlueprintReadOnly)
	APlayerController* PlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float cameraMoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float cameraRotSpeed;

	TSubclassOf<ULEUserWidget> MainHUD;

	ULEUserWidget* MainUI;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//  Û±Í◊Ûº¸ + WASDQE |  Û±Í◊Ûº¸ + «∞∫Û“∆∂ØY-Axis => “∆∂Ø
	void CameraLeftMouseTransform();

	//  Û±Í”“º¸ + “∆∂Ø XY-Axis
	void CameraRightMouseTransform();

	//  Û±Íπˆ¬÷
	void CameraMouseWheelTransform(float value);

	void ShowHideMainUI();


protected:
	void MultiCastDelKeyDown();

	void MultiCastRenameKeyDown();

	void MultiCastReplicateKeyDown();

public:	
	UCameraComponent* CameraComp;

	UPROPERTY(BlueprintAssignable)
	FMultiCastAction OnDeleteKeyDown;

	UPROPERTY(BlueprintAssignable)
	FMultiCastAction OnRenameKeyDown;

	UPROPERTY(BlueprintAssignable)
	FMultiCastAction OnReplicateKeyDown;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ShowMouseCurser();

	void HideMouseCurser();
};
