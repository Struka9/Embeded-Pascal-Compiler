#include "SumaUnaria.h"


SumaUnaria::SumaUnaria(Expresion* expr)
{
	SetExpr(expr);
}


SumaUnaria::~SumaUnaria(void)
{
	delete expr;
}

Tipo* SumaUnaria::validarSemantico()
{
	Tipo* t = InformacionSemantica::GetInstance()->GetTablaTipos().find("INTEGER")->second;
	Tipo* t_expr = expr->validarSemantico();

	if ( !(t->EsEquivalente (t_expr )) )
		throw SemanticException("Operador unario suma no es aplicable para este tipo");

	return t_expr;
}

Valor* SumaUnaria::interpretar()
{
	return expr->interpretar();
}