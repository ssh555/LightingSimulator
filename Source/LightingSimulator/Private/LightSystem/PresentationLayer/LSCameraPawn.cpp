// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSystem/PresentationLayer/LSCameraPawn.h"
#include <Camera/CameraComponent.h>
#include <Kismet/KismetSystemLibrary.h>
#include <GameFramework/PlayerController.h>
#include "LightSystem/LightStudioGameMode.h"
#include "LightSystem/PresentationLayer/LEUserWidget.h"
#include <UObject/UObjectGlobals.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
ALSCameraPawn::ALSCameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	this->CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	this->CameraComp->SetupAttachment(this->RootComponent);
	this->SetRootComponent(this->CameraComp);

	this->cameraMoveSpeed = 50;
	this->cameraRotSpeed = 2;


}

// Called when the game starts or when spawned
void ALSCameraPawn::BeginPlay()
{
	Super::BeginPlay();

	this->PlayerController = Cast<APlayerController>(this->GetController());

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);
	this->PlayerController->SetInputMode(InputMode);

	this->ShowMouseCurser();

	this->InputComponent->BindAxisKey(EKeys::MouseY);
	this->InputComponent->BindAxisKey(EKeys::MouseX);

	this->MainHUD = LoadClass<ULEUserWidget>(this, *(FString("WidgetBlueprint'/Game/LightingSimulator/UI/LightStudio/LE_MainHUD.LE_MainHUD_C'")));
	this->MainUI = Cast<ULEUserWidget>(CreateWidget(GetWorld(), this->MainHUD));
	this->MainUI->SetOwningPlayer(this->PlayerController);
	this->MainUI->AddToViewport();
}

// Called every frame
void ALSCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// 鼠标左键
	if (this->PlayerController->IsInputKeyDown(EKeys::LeftMouseButton)) {
		// 摄像机 Transform
		this->CameraLeftMouseTransform();
	}
	if (this->PlayerController->IsInputKeyDown(EKeys::RightMouseButton)) {
		this->CameraRightMouseTransform();
	}

	//PlayerInputComponent->BindAction("CameraMove", IE_Repeat, this, &ALSCameraPawn::TransLocation);
	// 鼠标左键 + Alt => 旋转

	// F => 以选定目标为中心，转换视口

	// Q

	// W

	// E

	// R
}

// Called to bind functionality to input
void ALSCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAction("ShowAndHideCurser", IE_Pressed, this, &ALSCameraPawn::HideMouseCurser);
	PlayerInputComponent->BindAction("ShowAndHideCurser", IE_Released, this, &ALSCameraPawn::ShowMouseCurser);
	PlayerInputComponent->BindAction("ShowHideMainUI", IE_Pressed, this, &ALSCameraPawn::ShowHideMainUI);

	PlayerInputComponent->BindAction("Delete", IE_Pressed, this, &ALSCameraPawn::MultiCastDelKeyDown);
	PlayerInputComponent->BindAction("Rename", IE_Pressed, this, &ALSCameraPawn::MultiCastRenameKeyDown);
	PlayerInputComponent->BindAction("Replicate", IE_Pressed, this, &ALSCameraPawn::MultiCastReplicateKeyDown);

	PlayerInputComponent->BindAxis("CameraForBackMove", this, &ALSCameraPawn::CameraMouseWheelTransform);
}

void ALSCameraPawn::CameraLeftMouseTransform()
{
	if (this->PlayerController->IsInputKeyDown(EKeys::W)) {
		this->AddActorLocalOffset(FVector::ForwardVector * this->cameraMoveSpeed);
	}
	else if (this->PlayerController->IsInputKeyDown(EKeys::S)) {
		this->AddActorLocalOffset(FVector::BackwardVector * this->cameraMoveSpeed);
	}
	else if (this->PlayerController->IsInputKeyDown(EKeys::A)) {
		this->AddActorLocalOffset(FVector::LeftVector * this->cameraMoveSpeed);
	}
	else if (this->PlayerController->IsInputKeyDown(EKeys::D)) {
		this->AddActorLocalOffset(FVector::RightVector * this->cameraMoveSpeed);
	}
	else if (this->PlayerController->IsInputKeyDown(EKeys::Q)) {
		this->AddActorLocalOffset(FVector::UpVector * this->cameraMoveSpeed);
	}
	else if (this->PlayerController->IsInputKeyDown(EKeys::E)) {
		this->AddActorLocalOffset(FVector::DownVector * this->cameraMoveSpeed);
	}
	else if (this->PlayerController->IsInputKeyDown(EKeys::LeftAlt) || this->PlayerController->IsInputKeyDown(EKeys::RightAlt)) {
		this->CameraRightMouseTransform();
	}
	else {
		float value = this->InputComponent->GetAxisKeyValue(EKeys::MouseY);
		this->AddActorLocalOffset(FVector::ForwardVector * this->cameraMoveSpeed * value);

		value = this->InputComponent->GetAxisKeyValue(EKeys::MouseX);
		this->AddActorWorldRotation(FRotator(0, this->cameraRotSpeed, 0) * value);
	}
}

void ALSCameraPawn::CameraRightMouseTransform()
{
	float Y_Axis = this->InputComponent->GetAxisKeyValue(EKeys::MouseY);
	float X_Axis = this->InputComponent->GetAxisKeyValue(EKeys::MouseX);

	this->AddActorWorldRotation((FRotator(0, X_Axis, 0) * this->cameraRotSpeed));
	this->AddActorLocalRotation((FRotator(Y_Axis, 0, 0) * this->cameraRotSpeed));
}

void ALSCameraPawn::CameraMouseWheelTransform(float value)
{
	if (!this->MainUI->IsHovered()) {
		this->AddActorLocalOffset(FVector::ForwardVector * this->cameraMoveSpeed * value);
	}
}

void ALSCameraPawn::ShowHideMainUI()
{
	if (this->MainUI->Visibility == ESlateVisibility::SelfHitTestInvisible) {
		this->MainUI->SetVisibility(ESlateVisibility::Collapsed);
	}
	else {
		this->MainUI->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

void ALSCameraPawn::ShowMouseCurser()
{
	this->PlayerController->SetShowMouseCursor(true);
}

void ALSCameraPawn::HideMouseCurser()
{
	this->PlayerController->SetShowMouseCursor(false);
}

void ALSCameraPawn::MultiCastDelKeyDown()
{
	this->OnDeleteKeyDown.Broadcast();
}

void ALSCameraPawn::MultiCastRenameKeyDown()
{
	this->OnRenameKeyDown.Broadcast();
}

void ALSCameraPawn::MultiCastReplicateKeyDown()
{
	this->OnReplicateKeyDown.Broadcast();
}
