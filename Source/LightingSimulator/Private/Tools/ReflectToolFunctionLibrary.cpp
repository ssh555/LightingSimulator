// Fill out your copyright notice in the Description page of Project Settings.


#include "Tools/ReflectToolFunctionLibrary.h"
#include <UObject/NoExportTypes.h>
#include <UObject/Class.h>
#include <HAL/Platform.h>
#include <Engine/DataTable.h>
#include <EditorFramework/AssetImportData.h>
#include "Tools/DataTableToolFunctionLibrary.h"

template<typename T>
T UReflectToolFunctionLibrary::GetPropertyValue(UObject* Target, FString PropertyName)
{
	return GetPropertyValue<T>(Target, FName(*PropertyName));
}

template<typename T>
T UReflectToolFunctionLibrary::GetPropertyValue(UObject* Target, FName PropertyName)
{
	FProperty* property = Target->GetClass()->FindPropertyByName(PropertyName);
	T* value = property->ContainerPtrToValuePtr<T>(Target);

	return *value;
}

int UReflectToolFunctionLibrary::GetIntPropertyValue(UObject* Target, FName PropertyName)
{
	return GetPropertyValue<int>(Target, PropertyName);
}

FString UReflectToolFunctionLibrary::GetFStringPropertyValue(UObject* Target, FName PropertyName)
{
	return GetPropertyValue<FString>(Target, PropertyName);

}

FName UReflectToolFunctionLibrary::GetFNamePropertyValue(UObject* Target, FName PropertyName)
{
	return GetPropertyValue<FName>(Target, PropertyName);
}

float UReflectToolFunctionLibrary::GetFloatPropertyValue(UObject* Target, FName PropertyName)
{
	return GetPropertyValue<float>(Target, PropertyName);
}

bool UReflectToolFunctionLibrary::GetBoolPropertyValue(UObject* Target, FName PropertyName)
{
	return GetPropertyValue<bool>(Target, PropertyName);
}

int32 UReflectToolFunctionLibrary::GetInt32PropertyValue(UObject* Target, FName PropertyName)
{
	return GetPropertyValue<int32>(Target, PropertyName);
}



template<typename T>
bool UReflectToolFunctionLibrary::SetPropertyValue(UObject* Target, FString PropertyName, T value)
{
	return SetPropertyValue<T>(Target, FName(*PropertyName), value);
}
template<typename T>
bool UReflectToolFunctionLibrary::SetPropertyValue(UObject* Target, FName PropertyName, T value)
{
	FProperty* property = Target->GetClass()->FindPropertyByName(PropertyName);
	if (property != NULL) {
		T* oldValue = property->ContainerPtrToValuePtr<T>(Target);
		*oldValue = value;
		return true;
	}
	return false;
}

bool UReflectToolFunctionLibrary::SetIntPropertyValue(UObject* Target, FName PropertyName, int value)
{
	return SetPropertyValue<int>(Target, PropertyName, value);
}

bool UReflectToolFunctionLibrary::SetFStringPropertyValue(UObject* Target, FName PropertyName, FString value)
{
	return SetPropertyValue<FString>(Target, PropertyName, value);
}

bool UReflectToolFunctionLibrary::SetFNamePropertyValue(UObject* Target, FName PropertyName, FName value)
{
	return SetPropertyValue<FName>(Target, PropertyName, value);
}

bool UReflectToolFunctionLibrary::SetFloatPropertyValue(UObject* Target, FName PropertyName, float value)
{
	return SetPropertyValue<float>(Target, PropertyName, value);

}

bool UReflectToolFunctionLibrary::SetBoolPropertyValue(UObject* Target, FName PropertyName, bool value)
{
	return SetPropertyValue<bool>(Target, PropertyName, value);

}

bool UReflectToolFunctionLibrary::SetInt32PropertyValue(UObject* Target, FName PropertyName, int32 value)
{
	return SetPropertyValue<int32>(Target, PropertyName, value);

}

bool UReflectToolFunctionLibrary::ExeFunction(UObject* Target, FName FunctionName)
{
	if (Target == nullptr) {
		return false;
	}
	UFunction* Func = Target->FindFunction(FunctionName);
	if (Func) {
		// 1. 给方法所有参数分配空间,并初始化
		uint8* AllFuncParam = static_cast<uint8*>(FMemory_Alloca(Func->ParmsSize));
		FMemory::Memzero(AllFuncParam, Func->ParmsSize);

		// 2. 给所有参数赋值

		// 3. 调用方法
		Target->ProcessEvent(Func, AllFuncParam);
		return true;
	}
	return false;
}

template<typename T>
bool UReflectToolFunctionLibrary::ExeFunction(UObject* Target, FName FunctionName, T& param)
{
	if (Target == nullptr) {
		return false;
	}
	UFunction* Func = Target->FindFunction(FunctionName);
	if (Func) {
		// 1. 给方法所有参数分配空间,并初始化
		uint8* AllFuncParam = static_cast<uint8*>(FMemory_Alloca(Func->ParmsSize));
		FMemory::Memzero(AllFuncParam, Func->ParmsSize);

		// 2. 给所有参数赋值
		int i = 0;
		for (TFieldIterator<FProperty> IteratorOfParam(Func); IteratorOfParam; ++IteratorOfParam, ++i)
		{
			FProperty* FuncParam = *IteratorOfParam;
			FString FuncParamName = FuncParam->GetName();
			if (i == 0) {
				*FuncParam->ContainerPtrToValuePtr<T>(AllFuncParam) = param;
			}
		}

		// 3. 调用方法
		Target->ProcessEvent(Func, AllFuncParam);
		return true;
	}
	return false;
}

template<typename T, typename U>
bool UReflectToolFunctionLibrary::ExeFunction(UObject* Target, FName FunctionName, T& param1, U& param2)
{
	if (Target == nullptr) {
		return false;
	}
	UFunction* Func = Target->FindFunction(FunctionName);
	if (Func) {
		// 1. 给方法所有参数分配空间,并初始化
		uint8* AllFuncParam = static_cast<uint8*>(FMemory_Alloca(Func->ParmsSize));
		FMemory::Memzero(AllFuncParam, Func->ParmsSize);

		// 2. 给所有参数赋值
		int i = 0;
		for (TFieldIterator<FProperty> IteratorOfParam(Func); IteratorOfParam; ++IteratorOfParam, ++i)
		{
			FProperty* FuncParam = *IteratorOfParam;
			FString FuncParamName = FuncParam->GetName();
			if (i == 0) {
				*FuncParam->ContainerPtrToValuePtr<T>(AllFuncParam) = param1;
			}
			else if (i == 1) {
				*FuncParam->ContainerPtrToValuePtr<U>(AllFuncParam) = param2;
			}
		}

		// 3. 调用方法
		Target->ProcessEvent(Func, AllFuncParam);
		return true;
	}
	return false;
}

template<typename T, typename U, typename P>
bool UReflectToolFunctionLibrary::ExeFunction(UObject* Target, FName FunctionName, T& param1, U& param2, P& param3)
{
	if (Target == nullptr) {
		return false;
	}
	UFunction* Func = Target->FindFunction(FunctionName);
	if (Func) {
		// 1. 给方法所有参数分配空间,并初始化
		uint8* AllFuncParam = static_cast<uint8*>(FMemory_Alloca(Func->ParmsSize));
		FMemory::Memzero(AllFuncParam, Func->ParmsSize);

		// 2. 给所有参数赋值
		int i = 0;
		for (TFieldIterator<FProperty> IteratorOfParam(Func); IteratorOfParam; ++IteratorOfParam, ++i)
		{
			FProperty* FuncParam = *IteratorOfParam;
			FString FuncParamName = FuncParam->GetName();
			if (i == 0) {
				*FuncParam->ContainerPtrToValuePtr<T>(AllFuncParam) = param1;
			}
			else if (i == 1) {
				*FuncParam->ContainerPtrToValuePtr<U>(AllFuncParam) = param2;
			}
			else if(i == 2) {
				*FuncParam->ContainerPtrToValuePtr<P>(AllFuncParam) = param3;

			}
		}

		// 3. 调用方法
		Target->ProcessEvent(Func, AllFuncParam);
		return true;
	}
	return false;
}

template<typename T, typename U, typename P, typename Q>
bool UReflectToolFunctionLibrary::ExeFunction(UObject* Target, FName FunctionName, T& param1, U& param2, P& param3, Q& param4)
{
	if (Target == nullptr) {
		return false;
	}
	UFunction* Func = Target->FindFunction(FunctionName);
	if (Func) {
		// 1. 给方法所有参数分配空间,并初始化
		uint8* AllFuncParam = static_cast<uint8*>(FMemory_Alloca(Func->ParmsSize));
		FMemory::Memzero(AllFuncParam, Func->ParmsSize);

		// 2. 给所有参数赋值
		int i = 0;
		for (TFieldIterator<FProperty> IteratorOfParam(Func); IteratorOfParam; ++IteratorOfParam, ++i)
		{
			FProperty* FuncParam = *IteratorOfParam;
			FString FuncParamName = FuncParam->GetName();
			if (i == 0) {
				*FuncParam->ContainerPtrToValuePtr<T>(AllFuncParam) = param1;
			}
			else if (i == 1) {
				*FuncParam->ContainerPtrToValuePtr<U>(AllFuncParam) = param2;
			}
			else if (i == 2) {
				*FuncParam->ContainerPtrToValuePtr<P> (AllFuncParam) = param3;

			}
			else if (i == 3) {
				*FuncParam->ContainerPtrToValuePtr<Q> (AllFuncParam) = param4;
			}
		}

		// 3. 调用方法
		Target->ProcessEvent(Func, AllFuncParam);
		return true;
	}
	return false;
}

template<typename T, typename U, typename P, typename Q, typename W>
bool UReflectToolFunctionLibrary::ExeFunction(UObject* Target, FName FunctionName, T& param1, U& param2, P& param3, Q& param4, W& param5)
{
	if (Target == nullptr) {
		return false;
	}
	UFunction* Func = Target->FindFunction(FunctionName);
	if (Func) {
		// 1. 给方法所有参数分配空间,并初始化
		uint8* AllFuncParam = static_cast<uint8*>(FMemory_Alloca(Func->ParmsSize));
		FMemory::Memzero(AllFuncParam, Func->ParmsSize);

		// 2. 给所有参数赋值
		int i = 0;
		for (TFieldIterator<FProperty> IteratorOfParam(Func); IteratorOfParam; ++IteratorOfParam, ++i)
		{
			FProperty* FuncParam = *IteratorOfParam;
			FString FuncParamName = FuncParam->GetName();
			if (i == 0) {
				*FuncParam->ContainerPtrToValuePtr<T>(AllFuncParam) = param1;
			}
			else if (i == 1) {
				*FuncParam->ContainerPtrToValuePtr<U>(AllFuncParam) = param2;
			}
			else if (i == 2) {
				*FuncParam->ContainerPtrToValuePtr<P>(AllFuncParam) = param3;

			}
			else if (i == 3) {
				*FuncParam->ContainerPtrToValuePtr<Q>(AllFuncParam) = param4;
			}
			else if (i == 4) {
				*FuncParam->ContainerPtrToValuePtr<W>(AllFuncParam) = param5;
			}
		}

		// 3. 调用方法
		Target->ProcessEvent(Func, AllFuncParam);
		return true;
	}
	return false;
}


