#include "AndBinario.h"


AndBinario::AndBinario(Expresion* op1,Expresion* op2)
{
	SetOpOne(op1);
	SetOpTwo(op2);
}


AndBinario::~AndBinario(void)
{
	delete op1;
	delete op2;
}

Tipo* AndBinario::validarSemantico()
{
	Tipo* t_op1 = op1->validarSemantico();
	Tipo* t_op2 = op2->validarSemantico();

	if ( t_op1->GetTipo() != t_boolean || t_op2->GetTipo() != t_boolean)
		throw SemanticException("El operador And solo es aplicable a tipo booleano");

	return t_op1;
}

Valor* AndBinario::interpretar()
{
	ValorBooleano* v_op1 = (ValorBooleano*)op1->interpretar();
	ValorBooleano* v_op2 = (ValorBooleano*)op2->interpretar();

	return new ValorBooleano( v_op1->GetVal() && v_op2->GetVal() );
}