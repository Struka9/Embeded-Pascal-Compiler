#include "SentenciaFor.h"


SentenciaFor::SentenciaFor(Identificador* id, Expresion* inicializacion, direccion dir, 
		Expresion* condicion, Sentencia* codigo)
{
	SetSiguiente(0);
	SetId(id);
	SetInicializacion(inicializacion);
	SetDir(dir);
	SetCondicion(condicion);
	SetCodigo(codigo);
}


SentenciaFor::~SentenciaFor(void)
{
	delete siguiente;
	delete inicializacion;
	delete condicion;
	delete codigo;
}

void SentenciaFor::SetCodigo( Sentencia* stmt)
{
	this->codigo = stmt;
}

void SentenciaFor::SetCondicion( Expresion* expr)
{
	this->condicion = expr;
}

void SentenciaFor::SetDir( direccion dir)
{
	this->dir = dir;
}

void SentenciaFor::SetId( Identificador* id )
{
	this->id = id;
}

void SentenciaFor::SetInicializacion( Expresion* expr )
{
	this->inicializacion = expr;
}

Sentencia* SentenciaFor::GetCodigo()
{
	return codigo;
}

Expresion* SentenciaFor::GetCondicion()
{
	return condicion;
}

direccion SentenciaFor::GetDir()
{
	return dir;
}

Identificador* SentenciaFor::GetId()
{
	return id;
}

Expresion* SentenciaFor::GetInicializacion()
{
	return inicializacion;
}

void SentenciaFor::validarSemantica()
{
	Tipo* tipo_id = id->validarSemantico();
	if ( tipo_id->GetTipo() != t_entero )
		throw SemanticException("El identificador debe de ser tipo entero");

	Tipo* tipo_expr = inicializacion->validarSemantico();
	if ( tipo_expr->GetTipo() != t_entero )
		throw SemanticException("La expresion de inicializacion debe ser tipo entero");

	Tipo* tipo_condicion = condicion->validarSemantico();
	if ( tipo_condicion->GetTipo() != t_entero )
		throw SemanticException("La condicion debe de ser tipo entero");

	if ( codigo != 0 )
		codigo->validacionSemantica();

}

void SentenciaFor::Interpretar()
{
	SentenciaAsignacion* asignacion = new SentenciaAsignacion(id,inicializacion);
	asignacion->Interpretacion();

	ValorEntero* val_condicion =(ValorEntero*) condicion->interpretar();

	if ( dir == ascendente )
	{
		while ( ((ValorEntero*)id->interpretar())->GetVal() <= val_condicion->GetVal() )
		{
			codigo->Interpretacion();

			asignacion->SetExpresion( new Suma( id,new ConstanteEntera(1) ) );
			asignacion->Interpretacion();
		}
	}
	else
	{
		while ( ((ValorEntero*)id->interpretar())->GetVal() >= val_condicion->GetVal() )
		{
			codigo->Interpretacion();

			asignacion->SetExpresion( new Resta( id,new ConstanteEntera(1) ) );
			asignacion->Interpretacion();
		}
	}
}