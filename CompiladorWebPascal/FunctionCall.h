#pragma once
#include "InformacionInterpretacion.h"
#include "Expresion.h"
#include "Identificador.h"
#include <list>
#include <string>
using namespace std;
class FunctionCall: public Expresion
{
private:
	list<Expresion*> argument_list;
	string function_name;
public:
	//PENDIENTE validar semantico
	FunctionCall(string function_name, list<Expresion*> arguments);
	~FunctionCall(void);
	void SetFunctionName(string func_name);
	void SetArguments(list<Expresion*> args );
	string GetFunctionName();
	list<Expresion*> GetArguments();
	Tipo* validarSemantico();
	Valor* interpretar();
};

