#include "SentenciaAsignacion.h"


SentenciaAsignacion::SentenciaAsignacion(Identificador* id,Expresion* expr)
{
	SetSiguiente(0);
	SetId(id);
	SetExpresion(expr);
}


SentenciaAsignacion::~SentenciaAsignacion(void)
{
	delete siguiente;
	delete id;
	delete expr;
}

void SentenciaAsignacion::SetId(Identificador* id)
{
	this->id = id;
}

void SentenciaAsignacion::SetExpresion(Expresion* expr)
{
	this->expr = expr;
}

Identificador* SentenciaAsignacion::GetId()
{
	return id;
}

Expresion* SentenciaAsignacion::GetExpresion()
{
	return expr;
}

void SentenciaAsignacion::validarSemantica()
{
	Tipo* tipo_id = id->validarSemantico();
	Tipo* tipo_expr = expr->validarSemantico();

	if ( !(tipo_id->EsEquivalente( tipo_expr ) ) )
		throw SemanticException("Los tipos no son compatibles SentenciaAsignacion.cpp");

}

void SentenciaAsignacion::Interpretar()
{
	Valor* val_expr = expr->interpretar();
	id->GuardarEnTablaValores( val_expr);
}