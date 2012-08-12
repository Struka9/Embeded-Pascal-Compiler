#include "SentenciaIf.h"


SentenciaIf::SentenciaIf( Expresion* condicion , 
	Sentencia* verdaderoStmt, Sentencia* falsoStmt)
{
	SetSiguiente(0);
	SetCondicion(condicion);
	SetSentenciaVerdadero(verdaderoStmt);
	SetSentenciaFalso(falsoStmt);
}


SentenciaIf::~SentenciaIf(void)
{
	delete condicion;
	delete verdaderoStmt;
	delete falsoStmt;
}

void SentenciaIf::SetCondicion(Expresion* expr)
{
	this->condicion = expr;
}

void SentenciaIf::SetSentenciaVerdadero( Sentencia* stmt)
{
	this->verdaderoStmt = stmt;
}

void SentenciaIf::SetSentenciaFalso( Sentencia* stmt )
{
	this->falsoStmt = stmt;
}

Expresion* SentenciaIf::GetCondicion()
{
	return condicion;
}

Sentencia* SentenciaIf::GetSentenciaVerdadero()
{
	return verdaderoStmt;
}

Sentencia* SentenciaIf::GetSentenciaFalso()
{
	return falsoStmt;
}

void SentenciaIf::validarSemantica()
{
	Tipo* t_condicion = condicion->validarSemantico();
	if ( t_condicion->GetTipo() != t_boolean)
		throw SemanticException("La condicion debe ser de tipo booleano");

	if ( verdaderoStmt != 0 )
		verdaderoStmt->validacionSemantica();

	if ( falsoStmt !=0 )
		falsoStmt->validacionSemantica();
}

void SentenciaIf::Interpretar()
{
	ValorBooleano* val_condicion =(ValorBooleano*) condicion->interpretar();

	if ( val_condicion->GetVal() )
		verdaderoStmt->Interpretacion();
	else if ( !val_condicion->GetVal() && falsoStmt != 0 )
		falsoStmt->Interpretacion();
}