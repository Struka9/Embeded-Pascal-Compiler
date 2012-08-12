#include "SentenciaCase.h"


SentenciaCase::SentenciaCase(Expresion* evaluacion,list<ClausulaCase*> clausulas,Sentencia* stmt_defecto)
{
	SetSiguiente(0);
	SetEvaluacion(evaluacion);
	SetClausulas(clausulas);
	SetSentenciaDefecto(stmt_defecto);
}


SentenciaCase::~SentenciaCase(void)
{
	delete evaluacion;
	delete sentencia_defecto;
	delete siguiente;
}

void SentenciaCase::SetClausulas(list<ClausulaCase*> clausulas)
{
	this->clausulas = clausulas;
}

void SentenciaCase::SetEvaluacion(Expresion* expr)
{
	this->evaluacion = expr;
}

void SentenciaCase::SetSentenciaDefecto(Sentencia* stmt)
{
	this->sentencia_defecto = stmt;
}

list<ClausulaCase*> SentenciaCase::GetClausulas()
{
	return clausulas;
}

Expresion* SentenciaCase::GetEvaluacion()
{
	return evaluacion;
}

Sentencia* SentenciaCase::GetSentenciaDefecto()
{
	return sentencia_defecto;
}

void SentenciaCase::validarSemantica()
{
	Tipo* t_evaluacion = evaluacion->validarSemantico();

	if ( t_evaluacion->GetTipo() != t_entero && t_evaluacion->GetTipo() != t_caracter )
		throw SemanticException("Solo se permite expresiones tipo entero o caracter para la evaluacion del case");

	list<ClausulaCase*>::iterator it = clausulas.begin();
	for ( ; it != clausulas.end() ; it++)
	{
		ClausulaCase* clausula = (*it);
		clausula->GetCodigo()->validacionSemantica();
		Tipo* t_clausula = clausula->GetConstante()->validarSemantico();

		if ( t_clausula->GetTipo() != t_evaluacion->GetTipo() )
			throw SemanticException("El tipo de la clausula debe coincidir con el de la expresion que se evalua");
	}

	if ( sentencia_defecto != 0 )
		sentencia_defecto->validacionSemantica();
}

void SentenciaCase::Interpretar()
{
	Valor* v_evaluacion = evaluacion->interpretar();

	if ( v_evaluacion->GetTipoValor() == entero )
	{
		ValorEntero* v_ent_evaluacion= (ValorEntero*)v_evaluacion;

		list<ClausulaCase*>::iterator it = clausulas.begin();
		bool ejecutoClausula = false;

		for ( ; it != clausulas.end() ; it++ )
		{
			ValorEntero* v_clausula_lit =(ValorEntero*)(*it)->GetConstante()->interpretar();

			if ( v_ent_evaluacion->GetVal() == v_clausula_lit->GetVal() )
			{
				(*it)->GetCodigo()->Interpretacion();
				ejecutoClausula = true;
			}
		}

		if ( !ejecutoClausula && sentencia_defecto != NULL )
			sentencia_defecto->Interpretacion();
	}
	else
	{
		ValorCaracter* v_char_evaluacion = (ValorCaracter*)v_evaluacion;

		list<ClausulaCase*>::iterator it = clausulas.begin();
		bool ejecutoClausula = false;

		for ( ; it != clausulas.end() ; it++ )
		{
			ValorCaracter* v_clausula_lit =(ValorCaracter*)(*it)->GetConstante()->interpretar();

			if ( v_char_evaluacion->GetVal().compare(v_clausula_lit->GetVal() )==0 )
			{
				(*it)->GetCodigo()->Interpretacion();
				ejecutoClausula = true;
			}
		}

		if ( !ejecutoClausula && sentencia_defecto != NULL )
			sentencia_defecto->Interpretacion();
	}
}