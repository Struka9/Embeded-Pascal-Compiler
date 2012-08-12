#pragma once
#include "Sentencia.h"
#include "FunctionCall.h"
#include <string>
#include <list>
using namespace std;

class SentenciaProcedimiento :
	public Sentencia
{
private:
	void Interpretar();
	FunctionCall* function;

public:
	SentenciaProcedimiento(FunctionCall* function_call);
	~SentenciaProcedimiento(void);
	void SetFunction(FunctionCall* function );
	FunctionCall* GetFunction();
	void validarSemantica();
};

