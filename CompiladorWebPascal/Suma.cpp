#include "Suma.h"


Suma::Suma(Expresion* op1, Expresion* op2)
{
	SetOpOne(op1);
	SetOpTwo(op2);
}


Suma::~Suma(void)
{
	delete op1;
	delete op2;
}

Tipo* Suma::validarSemantico()
{
	Tipo* t_expr1 = op1->validarSemantico();
	Tipo* t_expr2 = op2->validarSemantico();

	if ( t_expr1->GetTipo() == t_entero && t_expr2->GetTipo() == t_entero )
		return t_expr1;

	if ( t_expr1->GetTipo() == t_real && t_expr2->GetTipo() == t_real )
		return t_expr1;

	if ( t_expr1->GetTipo() == t_real && t_expr2->GetTipo() == t_entero )
		return t_expr1;

	if ( t_expr1->GetTipo() == t_entero && t_expr2->GetTipo() == t_real )
		return t_expr2;

	if ( t_expr1->GetTipo() == t_cadena && t_expr2->GetTipo() == t_cadena )
		return t_expr1;

	if ( t_expr1->GetTipo()==t_cadena && t_expr2->GetTipo() == t_caracter)
		return t_expr1;

	if ( t_expr1->GetTipo() == t_caracter && t_expr2->GetTipo() == t_cadena )
		return t_expr2;

	if ( t_expr1->GetTipo() == t_entero && t_expr2->GetTipo() == t_caracter )
		return t_expr2;

	if ( t_expr1->GetTipo() == t_caracter && t_expr2->GetTipo() == t_entero )
		return t_expr1;

	throw SemanticException("Operador de suma no es aplicable para estos tipos");
}

Valor* Suma::interpretar()
{
	Valor* v_expr1 = op1->interpretar();
	Valor* v_expr2 = op2->interpretar();

	if ( v_expr1->GetTipoValor()==entero && v_expr2->GetTipoValor() == entero )
	{
		ValorEntero* v_ent_expr1 = (ValorEntero*)v_expr1;
		ValorEntero* v_ent_expr2 = (ValorEntero*)v_expr2;
		int result = v_ent_expr1->GetVal() + v_ent_expr2->GetVal() ;

		return new ValorEntero( result );
	}
	else if ( v_expr1->GetTipoValor()==real && v_expr2->GetTipoValor()==real)
	{
		ValorReal* v_real_expr1 = (ValorReal*)v_expr1;
		ValorReal* v_real_expr2 = (ValorReal*)v_expr2;

		double result = v_real_expr1->GetVal() + v_real_expr2->GetVal() ;

		return new ValorReal(result);
	}
	else if ( v_expr1->GetTipoValor() == real && v_expr2->GetTipoValor()==entero )
	{
		ValorReal* v_real_expr1 = (ValorReal*)v_expr1;
		ValorEntero* v_ent_expr2 = (ValorEntero*)v_expr2;

		double result = v_real_expr1->GetVal() + (double)v_ent_expr2->GetVal();

		return new ValorReal(result);
	}
	else if(v_expr1->GetTipoValor() == entero && v_expr2->GetTipoValor()==real)
	{
		ValorEntero* v_ent_expr1 = (ValorEntero*)v_expr1;
		ValorReal* v_real_expr2 = (ValorReal*)v_expr2;

		double result = (double)v_ent_expr1->GetVal() + v_real_expr2->GetVal();

		return new ValorReal(result);
	}
	else if ( v_expr1->GetTipoValor()==entero && v_expr2->GetTipoValor()==caracter)
	{
		ValorEntero* v_ent_expr1 = (ValorEntero*)v_expr1;
		ValorCaracter* v_char_expr2 = (ValorCaracter*)v_expr2;

		char val_expr2 = v_char_expr2->GetVal().at(1);
		int val_expr1 = v_ent_expr1->GetVal();

		char result = (char)(val_expr2 + val_expr1);
		string nueva ="";
		nueva.push_back(result);

		return new ValorCaracter(nueva);
	}
	else if ( v_expr1->GetTipoValor() == caracter && v_expr2->GetTipoValor()==entero)
	{
		ValorEntero* v_ent_expr2 = (ValorEntero*)v_expr2;
		ValorCaracter* v_char_expr1 = (ValorCaracter*)v_expr1;

		char val_expr2 = v_char_expr1->GetVal().at(1);
		int val_expr1 = v_ent_expr2->GetVal();

		char result = (char)(val_expr2 + val_expr1);
		string nueva ="";
		nueva.push_back(result);

		return new ValorCaracter(nueva);
	}
}