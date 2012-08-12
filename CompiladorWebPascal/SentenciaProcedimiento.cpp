#include "SentenciaProcedimiento.h"


SentenciaProcedimiento::SentenciaProcedimiento(FunctionCall* function_call)
{
	SetSiguiente(0);
	SetFunction(function_call);
}


SentenciaProcedimiento::~SentenciaProcedimiento(void)
{
	delete function;
	delete siguiente;
}

void SentenciaProcedimiento::SetFunction(FunctionCall* function )
{
	this->function = function;
}

FunctionCall* SentenciaProcedimiento::GetFunction()
{
	return function;
}

void SentenciaProcedimiento::validarSemantica()
{
	Tipo* t = function->validarSemantico();

	if ( t != NULL )
		throw SemanticException("Esta intentando llamar una funcion como procedimiento");
}

void SentenciaProcedimiento::Interpretar()
{
	function->interpretar();
}