#include "SentenciaWrite.h"


SentenciaWrite::SentenciaWrite(Expresion* expr)
{
	SetSiguiente(0);
	SetExpresion(expr);
}


SentenciaWrite::~SentenciaWrite(void)
{
	delete expr;
	delete siguiente;
}

void SentenciaWrite::SetExpresion(Expresion* expr)
{
	this->expr = expr;
}

Expresion* SentenciaWrite::GetExpresion()
{
	return expr;
}

void SentenciaWrite::validarSemantica()
{
	Tipo* t = expr->validarSemantico();

	if ( t->GetTipo() == t_registro  )
		throw SemanticException("La sentencia write no es aplicable a registro");

	if ( t->GetTipo() == t_arreglo )
		throw SemanticException("La sentencia WRITE no es aplicable a arreglo");
}

void SentenciaWrite::Interpretar()
{
	Valor* v = expr->interpretar();

	if ( v->GetTipoValor() == entero )
	{
		ValorEntero* v_ent = (ValorEntero*)v;

		cout<< v_ent->GetVal() ;
	}
	else if ( v->GetTipoValor() == real )
	{
		ValorReal* v_real = (ValorReal*)v;

		cout<<v_real->GetVal();
	}

	else if ( v->GetTipoValor() == caracter )
	{
		ValorCaracter* v_char = (ValorCaracter*)v;
		cout<<v_char->GetVal();
	}
	else if ( v->GetTipoValor() == cadena )
	{
		ValorCadena* v_cadena = (ValorCadena*)v;
		cout<<v_cadena->GetValor();
	}
	else if ( v->GetTipoValor() == boolean )
	{
		ValorBooleano* v_bool = (ValorBooleano*)v;
		
		if ( v_bool->GetVal() )
			cout<<"TRUE";
		else
			cout<<"FALSE";
	}
	

	cout<<"\n";
}