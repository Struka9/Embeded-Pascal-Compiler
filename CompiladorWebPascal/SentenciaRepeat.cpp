#include "SentenciaRepeat.h"


SentenciaRepeat::SentenciaRepeat(Sentencia* codigo,Expresion* condicion)
{
	SetSiguiente(0);
	SetCodigo(codigo);
	SetCondicion(condicion);
}


SentenciaRepeat::~SentenciaRepeat(void)
{
	delete condicion;
	delete codigo;
}

void SentenciaRepeat::SetCodigo(Sentencia* stmt)
{
	this->codigo = stmt;
}

void SentenciaRepeat::SetCondicion(Expresion* expr)
{
	this->condicion = expr;
}

Sentencia* SentenciaRepeat::GetCodigo()
{
	return codigo;
}

Expresion* SentenciaRepeat::GetCondicion()
{
	return condicion;
}

void SentenciaRepeat::validarSemantica()
{
	Tipo* t_condicion = condicion->validarSemantico();
	if ( t_condicion->GetTipo() != t_boolean )
		throw SemanticException("La condicion debe ser de tipo booleano");

	if ( codigo != 0 )
		codigo->validacionSemantica();
}

void SentenciaRepeat::Interpretar()
{
	do
	{
		codigo->Interpretacion();
	}while (  !( (ValorBooleano*)condicion->interpretar() )->GetVal() );

}