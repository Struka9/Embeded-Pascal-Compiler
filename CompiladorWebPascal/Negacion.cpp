#include "Negacion.h"


Negacion::Negacion(Expresion* expr)
{
	SetExpr(expr);
}


Negacion::~Negacion(void)
{
	delete expr;
}

Tipo* Negacion::validarSemantico()
{
	Tipo* t_expr = expr->validarSemantico();

	if ( t_expr->GetTipo() != t_boolean )
		throw SemanticException("El operador de negacion es aplicable a tipo booleano");

	return t_expr;
}

Valor* Negacion::interpretar()
{
	ValorBooleano* v_expr =(ValorBooleano*) expr->interpretar();
	return new ValorBooleano( !v_expr->GetVal() );
}