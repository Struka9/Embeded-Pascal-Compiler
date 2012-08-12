#include "OrBinario.h"


OrBinario::OrBinario(Expresion* op1,Expresion* op2)
{
	SetOpOne(op1);
	SetOpTwo(op2);
}


OrBinario::~OrBinario(void)
{
	delete op1;
	delete op2;
}

Tipo* OrBinario::validarSemantico()
{
	Tipo* t_expr1 = op1->validarSemantico();
	Tipo* t_expr2 = op2->validarSemantico();

	if ( t_expr1->GetTipo() != t_boolean || t_expr2->GetTipo() != t_boolean)
		throw SemanticException("El operador Or solo es aplicable a tipo boolean");

	return t_expr1;
}

Valor* OrBinario::interpretar()
{
	ValorBooleano* v_op1 = (ValorBooleano*)op1->interpretar();
	ValorBooleano* v_op2 = (ValorBooleano*)op2->interpretar();

	return new ValorBooleano( v_op1->GetVal() || v_op2->GetVal() );
}