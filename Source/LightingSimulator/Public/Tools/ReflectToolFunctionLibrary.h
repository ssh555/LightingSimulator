// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ReflectToolFunctionLibrary.generated.h"

class UObject;
class UDataTable;

/**
 * 
 */
UCLASS()
class LIGHTINGSIMULATOR_API UReflectToolFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
#pragma region 获取属性值
	/// <summary>
	/// 获取对象类的对应属性名的值
	/// T 为该值的类型
	/// </summary>
	template<typename T>
	UFUNCTION()
	static T GetPropertyValue(UObject* Target, FString PropertyName);

	/// <summary>
	/// 获取对象类的对应属性名的值
	/// T 为该值的类型
	/// </summary>
	template<typename T>
	UFUNCTION()
	static T GetPropertyValue(UObject* Target, FName PropertyName);

#pragma region 方便蓝图测试调用
	UFUNCTION(BlueprintCallable, Category = "ReflectTool|GetProperty")
	static int GetIntPropertyValue(UObject* Target, FName PropertyName);

	UFUNCTION(BlueprintCallable, Category = "ReflectTool|GetProperty")
	static FString GetFStringPropertyValue(UObject* Target, FName PropertyName);

	UFUNCTION(BlueprintCallable, Category = "ReflectTool|GetProperty")
	static FName GetFNamePropertyValue(UObject* Target, FName PropertyName);

	UFUNCTION(BlueprintCallable, Category = "ReflectTool|GetProperty")
	static float GetFloatPropertyValue(UObject* Target, FName PropertyName);

	UFUNCTION(BlueprintCallable, Category = "ReflectTool|GetProperty")
	static bool GetBoolPropertyValue(UObject* Target, FName PropertyName);

	UFUNCTION(BlueprintCallable, Category = "ReflectTool|GetProperty")
	static int32 GetInt32PropertyValue(UObject* Target, FName PropertyName);
#pragma endregion

#pragma endregion

#pragma region 设置属性值
	/// <summary>
	/// 设置属性值
	/// </summary>
	template<typename T>
	UFUNCTION()
	static bool SetPropertyValue(UObject* Target, FString PropertyName, T value);

	/// <summary>
	/// 设置属性值
	/// </summary>
	template<typename T>
	UFUNCTION()
	static bool SetPropertyValue(UObject* Target, FName PropertyName, T value);

#pragma region 方便蓝图测试调用
	UFUNCTION(BlueprintCallable, Category = "ReflectTool|SetProperty")
	static bool SetIntPropertyValue(UObject* Target, FName PropertyName, int value);

	UFUNCTION(BlueprintCallable, Category = "ReflectTool|SetProperty")
	static bool SetFStringPropertyValue(UObject* Target, FName PropertyName, FString value);

	UFUNCTION(BlueprintCallable, Category = "ReflectTool|SetProperty")
	static bool SetFNamePropertyValue(UObject* Target, FName PropertyName, FName value);

	UFUNCTION(BlueprintCallable, Category = "ReflectTool|SetProperty")
	static bool SetFloatPropertyValue(UObject* Target, FName PropertyName, float value);

	UFUNCTION(BlueprintCallable, Category = "ReflectTool|SetProperty")
	static bool SetBoolPropertyValue(UObject* Target, FName PropertyName, bool value);

	UFUNCTION(BlueprintCallable, Category = "ReflectTool|SetProperty")
	static bool SetInt32PropertyValue(UObject* Target, FName PropertyName, int32 value);
#pragma endregion

#pragma endregion


#pragma region 执行函数
	UFUNCTION(BlueprintCallable, Category = "ReflectTool|ExeFunction")
	static bool ExeFunction(UObject* Target, FName FunctionName);

	template<typename T>
	UFUNCTION(BlueprintCallable, Category = "ReflectTool|ExeFunction")
	static bool ExeFunction(UObject* Target, FName FunctionName, T& param);

	template<typename T, typename U>
	UFUNCTION(BlueprintCallable, Category = "ReflectTool|ExeFunction")
	static bool ExeFunction(UObject* Target, FName FunctionName, T& param1, U& param2);

	template<typename T, typename U, typename P>
	UFUNCTION(BlueprintCallable, Category = "ReflectTool|ExeFunction")
	static bool ExeFunction(UObject* Target, FName FunctionName, T& param1, U& param2, P& param3);

	template<typename T, typename U, typename P, typename Q>
	UFUNCTION(BlueprintCallable, Category = "ReflectTool|ExeFunction")
	static bool ExeFunction(UObject* Target, FName FunctionName, T& param1, U& param2, P& param3, Q& param4);

	template<typename T, typename U, typename P, typename Q, typename W>
	UFUNCTION(BlueprintCallable, Category = "ReflectTool|ExeFunction")
	static bool ExeFunction(UObject* Target, FName FunctionName, T& param1, U& param2, P& param3, Q& param4, W& param5);
#pragma endregion


};
