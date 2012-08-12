#include "SentenciaWhile.h"


SentenciaWhile::SentenciaWhile( Expresion* condicion, Sentencia* codigo)
{
	SetSiguiente(0);
	SetCodigo(codigo);
	SetCondicion(condicion);
}


SentenciaWhile::~SentenciaWhile(void)
{
	delete codigo;
	delete condicion;
	delete siguiente;
}


void SentenciaWhile::SetCodigo(Sentencia* stmt)
{
	this->codigo = stmt;
}

Sentencia* SentenciaWhile::GetCodigo()
{
	return codigo;
}

void SentenciaWhile::SetCondicion(Expresion* expr )
{
	this->condicion = expr;
}

Expresion* SentenciaWhile::GetCondicion()
{
	return condicion;
}

void SentenciaWhile::validarSemantica()
{
	Tipo* t_condicion = condicion->validarSemantico();
	if ( t_condicion->GetTipo() != t_boolean )
		throw SemanticException("La condicion debe ser de tipo booleano");

	if ( codigo != 0 )
		codigo->validacionSemantica();
}

void SentenciaWhile::Interpretar()
{
	while ( ((ValorBooleano*)condicion->interpretar() )->GetVal() )
		codigo->Interpretacion();
}