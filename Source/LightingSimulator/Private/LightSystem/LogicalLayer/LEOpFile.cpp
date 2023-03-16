// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSystem/LogicalLayer/LEOpFile.h"
#include "Tools/GamePathToolFunctionLibrary.h"
#include <Kismet/KismetSystemLibrary.h>
#include "LightSystem/LightStudioGameMode.h"
#include "Tools/FileHelperFunctionLibrary.h"
#include "LightSystem/LogicalLayer/SaveAndLoadData.h"
#include <Tools/ReflectToolFunctionLibrary.h>

LEOpFile::LEOpFile()
{
	this->Reset();
}

LEOpFile::~LEOpFile()
{
}

void LEOpFile::SetFile(FString fileName, USceneComponent* comp)
{
	if (!fileName.Contains(".leop")) {
		fileName.Append(".leop");
	}
	this->FileName = fileName;
	fileName = UGamePathToolFunctionLibrary::GetGameLEOPFile().Append(fileName);
	if (UFileHelperFunctionLibrary::FileExist(fileName)) {
		FFileHelper::LoadFileToStringArray(this->StringData, *(fileName));
	}
	this->OwnComp = comp;
}

void LEOpFile::Reset()
{
	this->curRow = 0;
	//this->LocalVarity.Empty();
}

bool LEOpFile::IsLocalValue(FString value)
{
	if (value == "")
		return false;
	if (value[0] == '$' && value[value.Len() - 1] == '$') {
		return true;
	}
	return false;
}


FString LEOpFile::GetLocalValueKey(FString value)
{
	return value.TrimChar('$');
}

void LEOpFile::Run(float DeltaTime)
{
	if (this->curRow >= this->StringData.Num())
	{
		if (this->bIsAutoReset && this->curRow != 0)
		{
			this->Reset();
		}
		else
		{
			return;
		}
	}

	this->Execute();

	//for (auto var : LocalVarity)
	//{
	//	ALightStudioGameMode::PrintString(FileName + " :: " + var.Key + " : " + var.Value.value);
	//}
}

LEOpFile::LEOPValue LEOpFile::Execute()
{
	LEOPValue ret;
	while (this->curRow < this->StringData.Num())
	{
		ret = this->Execute(this->StringData[this->curRow]);
		++(this->curRow);
	}
	return ret;
}

LEOpFile::LEOPValue LEOpFile::Execute(FString Code)
{
	LEOPValue ret;
	if (Code.IsEmpty())
	{
		return ret;
	}
	TArray<FString> _code;
	Code.ParseIntoArray(_code, *(FString(" ")), true);

	// 第一行
	if (this->curRow == 0) {
		// 第一个为返回值
		ret.type = GetLEOPValType(_code[0]);
		// 剩余为参数,加入局部变量字典
		for (int i = 1; i < _code.Num(); i += 2) {
			if (LocalVarity.Contains(_code[i+1]))
				continue;
			LEOPValue val;
			val.type = this->GetLEOPValType(_code[i]);
			this->InitLEOPVal(val);
			LocalVarity.Add(_code[i + 1], val);
		}
	}
	// 只是一个变量
	else if (IsLocalValue(Code)) {
		return *(LocalVarity.Find(GetLocalValueKey(Code)));
	}
	else {
		for (int i = 0; i < _code.Num(); ++i) {
			// 声明局部变量
			if (this->GetLEOPValType(_code[i]) != LEOPValType::ERROR) {
				LEOPValType type = this->GetLEOPValType(_code[i]);
				for (int j = 1; i+j < _code.Num(); ++j) {
					if(LocalVarity.Contains(_code[i+j]))
						continue;
					LEOPValue val;
					val.type = type;
					this->InitLEOPVal(val);
;					LocalVarity.Add(_code[j+i], val);
				}
				break;
			}
			// 局部变量赋值
			else if (_code[i] == "SET") {
				if (IsLocalValue(_code[i + 1])) {
					LEOPValue* val1 = (LocalVarity.Find(GetLocalValueKey(_code[i + 1])));
					FString __codes = "";
					for (int j = i + 2; j < _code.Num(); ++j) {
						__codes += _code[j] + " ";
					}
					__codes = __codes.TrimStartAndEnd();
					val1->value = Execute(__codes).value;
				}
				break;
			}
			// 返回局部变量的值
			// if
			else if (_code[i] == "IF") {
				Code = Code.Right(Code.Len() - 2 - Code.Find("IF")).TrimStartAndEnd();
				// if true 直接结束，Execute()会自动进入if内的下一行
				// if false 跳跃至最近的 IFEND
				if (!LEOPValToBool(Execute(Code))) {
					for (;this->curRow < this->StringData.Num(); ++this->curRow) {
						if (this->StringData[this->curRow] == ("IFEND")) {
							return ret;
						}
					}
				}
				
			}
			// 比较
			else if (_code[i] == "EQUAL" || _code[i] == "NOTEQUAL" || _code[i] == "GREATER" || _code[i] == "LESS" || _code[i] == "EGREATER" || _code[i] == "ELESS") {
				ret.type = LEOPValType::STRING;
				ret.value = LEOPValComp(Execute(_code[i + 1]), Execute(_code[i + 2]), _code[i]) ? "true" : "false";
				return ret;
			}
			// EXE
			else if (_code[i] == "EXE") {
				LEOpFile exeFile;
				exeFile.SetFile(_code[i + 1], this->OwnComp);
				TArray<FString> exeCode;
				exeFile.StringData[0].ParseIntoArray(exeCode, *(FString(" ")), true);
				// 剩余为参数,加入局部变量字典
				for (int j = 1,k = 2; j < _code.Num(); j += 2, ++k) {
					if (exeFile.LocalVarity.Contains(exeCode[j + 1]))
						continue;
					LEOPValue val;
					val.type = this->GetLEOPValType(exeCode[j]);
					val.value = Execute(_code[i + k]).value;
					exeFile.LocalVarity.Add(exeCode[j + 1], val);
					return exeFile.Execute();
				}
			}
			// RETURN
			else if (_code[i] == "RETURN") {
				Code = Code.Right(Code.Len() - 6 - Code.Find("RETURN")).TrimStartAndEnd();
				ret = Execute(Code);
				return ret;
			}
			// FOR
			else if (_code[i] == "FOR") {
				FString _initCode, _conditionCode, _loopCode;
				int j;
				for (j = i + 1; _code[j] != "|"; ++j) {
					_initCode += _code[j] + " ";
				}
				_initCode.TrimStartAndEndInline();

				for (++j; _code[j] != "|"; ++j) {
					_conditionCode += _code[j] + " ";
				}
				_conditionCode.TrimStartAndEndInline();

				for (++j; j < _code.Num(); ++j) {
					_loopCode += _code[j] + " ";
				}
				_loopCode.TrimStartAndEndInline();

				int forRow = this->curRow;
				for (Execute(_initCode); LEOPValToBool(Execute(_conditionCode)); Execute(_loopCode), this->curRow = forRow) {
					LEOPValue res;
					while (this->StringData[++this->curRow] != "FOREND")
					{
						res = Execute(this->StringData[this->curRow]);
						if(res.value == "BREAK" || res.value == "CONTINUE")
							break;
					}
					if (res.value == "BREAK") {
						break;
					}
					else if (res.value == "CONTINUE") {
						continue;
					}
				}
				return ret;
			}
			// ADD SUB MUL DIV
			else if (_code[i] == "ADD" || _code[i] == "SUB" || _code[i] == "MUL" || _code[i] == "DIV") {
				LEOPValue val1 = Execute(_code[i + 1]);
				LEOPValue val2 = Execute(_code[i + 2]);
				LEOPValOperation(val1, val2, _code[i]);
				LocalVarity.Find(_code[i + 1].TrimChar('$'))->value = val1.value;
			}
			// GETDATA
			else if (_code[i] == "GETDATA") {
				ISaveAndLoadData* ISL = Cast<ISaveAndLoadData>(this->OwnComp);
				ret.value = ISL->GetData(Execute(_code[i + 1]).value);
				ret.type = LEOPValType::STRING;
				return ret;
			}
			// SETDATA
			else if (_code[i] == "SETDATA") {
				ISaveAndLoadData* ISL = Cast<ISaveAndLoadData>(this->OwnComp);
				ISL->SetData(Execute(_code[i + 1]).value, Execute(_code[i + 2]).value);
				return ret;
			}
			// AddLocalOffset
			else if (_code[i] == "AddLocalOffset") {
				FVector offset;
				offset.InitFromString(FString(LEOPValReplace(_code[i + 1]) + " " + LEOPValReplace(_code[i + 2]) + " " + LEOPValReplace(_code[i + 3])));
				this->OwnComp->AddLocalOffset(offset);
			}
			// AddLocalRotation
			else if (_code[i] == "AddLocalRotation") {
				FRotator rot;
				rot.InitFromString(FString(LEOPValReplace(_code[i + 1]) + " " + LEOPValReplace(_code[i + 2]) + " " + LEOPValReplace(_code[i + 3])));
				this->OwnComp->AddLocalRotation(rot);
			}
			// AddRelativeLocation
			else if (_code[i] == "AddRelativeLocation") {
				FVector offset;
				offset.InitFromString(FString(LEOPValReplace(_code[i + 1]) + " " + LEOPValReplace(_code[i + 2]) + " " + LEOPValReplace(_code[i + 3])));
				this->OwnComp->AddRelativeLocation(offset);
			}
			// AddRelativeRotation
			else if (_code[i] == "AddRelativeRotation") {
				FRotator rot;
				rot.InitFromString(FString(LEOPValReplace(_code[i + 1]) + " " + LEOPValReplace(_code[i + 2]) + " " + LEOPValReplace(_code[i + 3])));
				this->OwnComp->AddRelativeRotation(rot);
			}
			// AddWorldOffset
			else if (_code[i] == "AddWorldOffset") {
				FVector offset;
				offset.InitFromString(FString(LEOPValReplace(_code[i + 1]) + " " + LEOPValReplace(_code[i + 2]) + " " + LEOPValReplace(_code[i + 3])));
				this->OwnComp->AddWorldOffset(offset);
			}
			// AddWorldRotation
			else if (_code[i] == "AddWorldRotation") {
				FRotator rot;
				rot.InitFromString(FString(LEOPValReplace(_code[i + 1]) + " " + LEOPValReplace(_code[i + 2]) + " " + LEOPValReplace(_code[i + 3])));
				this->OwnComp->AddWorldRotation(rot);
			}
			else if (_code[i] == "SETMAT_VECTOR") {
				ISaveAndLoadData* ISL = Cast<ISaveAndLoadData>(this->OwnComp);

				FLinearColor value;
				value.InitFromString(FString(LEOPValReplace(_code[i + 2])));
				ISL->MatInst->SetVectorParameterValue(FName(*_code[i + 1]), value);
			}
			else if (_code[i] == "SETMAT_SCALAR") {
				ISaveAndLoadData* ISL = Cast<ISaveAndLoadData>(this->OwnComp);

				float value = FCString::Atof(*LEOPValReplace(_code[i + 2]));
				ISL->MatInst->SetScalarParameterValue(FName(*_code[i + 1]), value);
			}
			else if (_code[i] == "SETMAT_TEXTURE") {
				ISaveAndLoadData* ISL = Cast<ISaveAndLoadData>(this->OwnComp);

				ISL->MatInst->SetTextureParameterValue(FName(*_code[i + 1]), LoadObject<UTexture>(this->OwnComp, *LEOPValReplace(_code[i + 2])));
			}

		}
	}
	//UMaterialInstanceDynamic* MatInst = UReflectToolFunctionLibrary::GetPropertyValue<UMaterialInstanceDynamic*>(this->OwnComp, FString("MatInst"));
	//MatInst->SetScalarParameterValue();
	//MatInst->SetTextureParameterValue();
	//MatInst->SetVectorParameterValue();
	ret.value = Code;
	return ret;
}

