#include "Modulo.h"


Modulo::Modulo(Expresion* op1,Expresion* op2)
{
	SetOpOne(op1);
	SetOpTwo(op2);
}


Modulo::~Modulo(void)
{
	delete op1;
	delete op2;
}

Tipo* Modulo::validarSemantico()
{
	Tipo* t_expr1 = op1->validarSemantico();
	Tipo* t_expr2 = op2->validarSemantico();

	if ( t_expr1->GetTipo() != t_entero || t_expr2->GetTipo() != t_entero )
	{
		throw SemanticException("El operador mod solo puede aplicarse a tipos enteros");
	}

	return t_expr1;
}

Valor* Modulo::interpretar()
{
	ValorEntero* v_expr1 =(ValorEntero*) op1->interpretar();
	ValorEntero* v_expr2 =(ValorEntero*) op2->interpretar();

	int result = v_expr1->GetVal() % v_expr2->GetVal() ;

	return new ValorEntero( result );
}