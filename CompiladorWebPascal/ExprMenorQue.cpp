#include "ExprMenorQue.h"


ExprMenorQue::ExprMenorQue(Expresion* izq, Expresion* der)
{
	SetOpOne(izq);
	SetOpTwo(der);
}


ExprMenorQue::~ExprMenorQue(void)
{
	delete op1;
	delete op2;
}

Tipo* ExprMenorQue::validarSemantico()
{
	Tipo* t_expr1 = op1->validarSemantico();
	Tipo* t_expr2 = op2->validarSemantico();

	Tipo* tipo_entero = InformacionSemantica::GetInstance()->GetTablaTipos().find("INTEGER")->second;
	Tipo* tipo_cadena = InformacionSemantica::GetInstance()->GetTablaTipos().find("STRING")->second;

	if ( t_expr1->GetTipo() == t_entero || t_expr1->GetTipo()==t_real )
	{
		if (  !(tipo_entero->EsEquivalente(t_expr2) ) )
			throw SemanticException("La expresion solo es aplicable a tipos compatibles");
	}
	else if ( t_expr1->GetTipo() == t_cadena || t_expr1->GetTipo()==t_caracter )
	{
		if ( !(tipo_cadena->EsEquivalente(t_expr2) ) )
			throw SemanticException("La expresion solo es aplicable a tipos compatibles");
	}
	else 
		throw SemanticException("La expresion no es aplicable a estos tipos");

	return InformacionSemantica::GetInstance()->GetTablaTipos().find("BOOLEAN")->second;
}

Valor* ExprMenorQue::interpretar()
{
	Valor* v_expr1 = op1->interpretar();
	Valor* v_expr2 = op2->interpretar();

	if ( v_expr1->GetTipoValor() == entero && v_expr2->GetTipoValor()==entero)
	{
		ValorEntero* v_ent_expr1 = (ValorEntero*)v_expr1;
		ValorEntero* v_ent_expr2 = (ValorEntero*)v_expr2;

		return new ValorBooleano(v_ent_expr1->GetVal() < v_ent_expr2->GetVal() );
	}
	else if ( v_expr1->GetTipoValor()==entero && v_expr2->GetTipoValor() == real)
	{
		ValorEntero* v_ent_expr1 = (ValorEntero*)v_expr1;
		ValorReal* v_real_expr2 = (ValorReal*)v_expr2;

		return new ValorBooleano( ((double)v_ent_expr1->GetVal()) < v_real_expr2->GetVal() );
	}
	else if ( v_expr1->GetTipoValor() == real && v_expr2->GetTipoValor() == entero )
	{
		ValorReal* v_real_expr1 = (ValorReal*)v_expr1;
		ValorEntero* v_ent_expr2 = (ValorEntero*)v_expr2;

		return new ValorBooleano( v_real_expr1->GetVal() < ((double)v_ent_expr2->GetVal() ) );
	}
	else if ( v_expr1->GetTipoValor() == real && v_expr2->GetTipoValor()==real )
	{
		ValorReal* v_real_expr1 = (ValorReal*)v_expr1;
		ValorReal* v_real_expr2 = (ValorReal*)v_expr2;

		return new ValorBooleano( v_real_expr1->GetVal() < v_real_expr2->GetVal() );
	}
	else if ( v_expr1->GetTipoValor()==cadena && v_expr2->GetTipoValor()==cadena )
	{
		ValorCadena* v_str_expr1 = (ValorCadena*)v_expr1;
		ValorCadena* v_str_expr2 = (ValorCadena*)v_expr2;

		return new ValorBooleano( v_str_expr1->GetValor().size() < v_str_expr2->GetValor().size() );
	}
	else if ( v_expr1->GetTipoValor()==cadena && v_expr2->GetTipoValor()==caracter )
	{
		ValorCadena* v_str_expr1 = (ValorCadena*)v_expr1;
		ValorCaracter* v_char_expr2 = (ValorCaracter*)v_expr2;

		return new ValorBooleano( v_str_expr1->GetValor().size() < v_char_expr2->GetVal().size() );
	}
	else if ( v_expr1->GetTipoValor()==caracter && v_expr2->GetTipoValor()==cadena )
	{
		ValorCaracter* v_char_expr1 = (ValorCaracter*)v_expr1;
		ValorCadena* v_str_expr2 = (ValorCadena*)v_expr2;

		return new ValorBooleano( v_char_expr1->GetVal().size() < v_str_expr2->GetValor().size() );
	}
	else if ( v_expr1->GetTipoValor()==caracter && v_expr2->GetTipoValor()==caracter )
	{
		ValorCaracter* v_str_expr1 = (ValorCaracter*)v_expr1;
		ValorCaracter* v_str_expr2 = (ValorCaracter*)v_expr2;

		return new ValorBooleano( v_str_expr1->GetVal().size() < v_str_expr2->GetVal().size() );
	}
}