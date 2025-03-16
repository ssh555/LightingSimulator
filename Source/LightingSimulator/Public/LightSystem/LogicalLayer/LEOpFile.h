//// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class LIGHTINGSIMULATOR_API LEOpFile
{
	UENUM(BlueprintType)
	enum LEOPValType
	{
		VOID = 0,
		INT,
		STRING,
		FLOAT,
		ERROR = -1,
	};
	
	LEOPValType GetLEOPValType(FString type) {
		if (type == "VOID")
		{
			return LEOPValType::VOID;
		}
		else if(type == "INT")
		{
			return LEOPValType::INT;
		}
		else if (type == "STRING")
		{
			return LEOPValType::STRING;
		}
		else if (type == "FLOAT")
		{
			return LEOPValType::FLOAT;
		}
		return LEOPValType::ERROR;
	}

	struct LEOPValue
	{
		LEOPValType type;
		FString value;
	};
	void InitLEOPVal(LEOPValue& value) {
		if (value.type == LEOPValType::FLOAT)
		{
			value.value = "0.0f";
		}
		else if (value.type == LEOPValType::INT)
		{
			value.value = "0";
		}
		else if (value.type == LEOPValType::STRING)
		{
			value.value = "";
		}
	}
	bool LEOPValToBool(const LEOPValue& value) {
		if (value.type == LEOPValType::FLOAT) {
			return FCString::Atof(*value.value) != 0;
		}
		else if (value.type == LEOPValType::INT) {
			return FCString::Atoi(*value.value) != 0;
		}
		return value.value.ToBool();
	}
	bool LEOPValComp(const LEOPValue& val1, const LEOPValue& val2, const FString& compType) {
		if (compType == "EQUAL") {
			if (val1.type == LEOPValType::FLOAT) {
				return FCString::Atof(*val1.value) == FCString::Atof(*val2.value);
			}
			else if (val1.type == LEOPValType::INT) {
				return FCString::Atoi(*val1.value) == FCString::Atoi(*val2.value);
			}
			return val1.value == val2.value;
		}
		else if (compType == "NOTEQUAL") {
			if (val1.type == LEOPValType::FLOAT) {
				return FCString::Atof(*val1.value) != FCString::Atof(*val2.value);
			}
			else if (val1.type == LEOPValType::INT) {
				return FCString::Atoi(*val1.value) != FCString::Atoi(*val2.value);
			}
			return val1.value != val2.value;
		}
		else if (compType == "GREATER") {
			if (val1.type == LEOPValType::FLOAT) {
				return FCString::Atof(*val1.value) > FCString::Atof(*val2.value);
			}
			else if (val1.type == LEOPValType::INT) {
				return FCString::Atoi(*val1.value) > FCString::Atoi(*val2.value);
			}
			return val1.value > val2.value;
		}
		else if (compType == "LESS") {
			if (val1.type == LEOPValType::FLOAT) {
				return FCString::Atof(*val1.value) < FCString::Atof(*val2.value);
			}
			else if (val1.type == LEOPValType::INT) {
				return FCString::Atoi(*val1.value) < FCString::Atoi(*val2.value);
			}
			return val1.value < val2.value;
		}
		else if (compType == "EGREATER") {
			if (val1.type == LEOPValType::FLOAT) {
				return FCString::Atof(*val1.value) >= FCString::Atof(*val2.value);
			}
			else if (val1.type == LEOPValType::INT) {
				return FCString::Atoi(*val1.value) >= FCString::Atoi(*val2.value);
			}
			return val1.value >= val2.value;
		}
		else if (compType == "ELESS") {
			if (val1.type == LEOPValType::FLOAT) {
				return FCString::Atof(*val1.value) <= FCString::Atof(*val2.value);
			}
			else if (val1.type == LEOPValType::INT) {
				return FCString::Atoi(*val1.value) <= FCString::Atoi(*val2.value);
			}
			return val1.value <= val2.value;
		}
		return false;
	}
	FString LEOPValReplace(const FString& str) {
		TArray<FString> _code;
		str.ParseIntoArray(_code, *(FString("$")), true);
		FString res = "";
		for (int i = 0; i < _code.Num(); ++i) {
			// 为变量
			if (i&1) {
				res += LocalVarity.Find(_code[i])->value;
			}
			// 直接附加
			else {
				res +=  _code[i];
			}
		}
		return res;
	}
	void LEOPValOperation(LEOPValue& val1, const LEOPValue& val2, const FString& opType) {
		if (opType == "ADD") {
			if (val1.type == LEOPValType::FLOAT) {
				val1.value = FString::SanitizeFloat(FCString::Atof(*val1.value) + FCString::Atof(*val2.value));
			}
			else if (val1.type == LEOPValType::INT) {
				val1.value = FString::FromInt(FCString::Atoi(*val1.value) + FCString::Atoi(*val2.value));
			}
			else
				val1.value += val2.value;
		}
		else if (opType == "SUB") {
			if (val1.type == LEOPValType::FLOAT) {
				val1.value = FString::SanitizeFloat(FCString::Atof(*val1.value) - FCString::Atof(*val2.value));
			}
			else if (val1.type == LEOPValType::INT) {
				val1.value = FString::FromInt(FCString::Atoi(*val1.value) - FCString::Atoi(*val2.value));
			}
		}
		else if (opType == "MUL") {
			if (val1.type == LEOPValType::FLOAT) {
				val1.value = FString::SanitizeFloat(FCString::Atof(*val1.value) * FCString::Atof(*val2.value));
			}
			else if (val1.type == LEOPValType::INT) {
				val1.value = FString::FromInt(FCString::Atoi(*val1.value) * FCString::Atoi(*val2.value));
			}
		}
		else if (opType == "DIV") {
			if (val1.type == LEOPValType::FLOAT) {
				val1.value = FString::SanitizeFloat(FCString::Atof(*val1.value) / FCString::Atof(*val2.value));
			}
			else if (val1.type == LEOPValType::INT) {
				val1.value = FString::FromInt(FCString::Atoi(*val1.value) / FCString::Atoi(*val2.value));
			}
		}
		else if (opType == "MOD") {
			if (val1.type == LEOPValType::INT) {
				val1.value = FString::FromInt(FCString::Atoi(*val1.value) % FCString::Atoi(*val2.value));
			}
		}
	}

protected:
	int curRow;

	TMap<FString, LEOPValue> LocalVarity;
	bool IsLocalValue(FString value);
	FString GetLocalValueKey(FString value);

	LEOPValue Execute(FString Code);


public:
	LEOPValue Execute();

	// 对应文件名称
	FString FileName;

	// 按行读入
	TArray<FString> StringData;

	bool bIsAutoReset = false;

	USceneComponent* OwnComp;

public:
	LEOpFile();
	~LEOpFile();

	void SetFile(FString fileName, USceneComponent* comp);

	void Run(float DeltaTime);

	void Reset();
};
