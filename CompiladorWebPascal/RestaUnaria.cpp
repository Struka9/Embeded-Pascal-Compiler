#include "RestaUnaria.h"


RestaUnaria::RestaUnaria(Expresion* expr)
{
	SetExpr(expr);
}


RestaUnaria::~RestaUnaria(void)
{
	delete expr;
}

Tipo* RestaUnaria::validarSemantico()
{
	Tipo* t = expr->validarSemantico();
	Tipo* tipo_real = InformacionSemantica::GetInstance()->GetTablaTipos().find("REAL")->second;

	if ( !(tipo_real->EsEquivalente( t ) ) )
		throw SemanticException("El operador unario resta no es aplicable para este tipo");

	return t;

	
}

Valor* RestaUnaria::interpretar()
{
	Valor* v = expr->interpretar();

	if ( v->GetTipoValor() == entero )
	{
		ValorEntero* v_entero = (ValorEntero*)v;

		int valor = -v_entero->GetVal();
		v_entero->SetVal(valor);

		return v_entero;
	}
	else if (v->GetTipoValor()==real)
	{
		ValorReal* v_real = (ValorReal*)v;
		double valor = -v_real->GetVal();

		v_real->SetVal(valor);
		return v_real;
	}
}