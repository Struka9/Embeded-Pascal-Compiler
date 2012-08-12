#include "ExpresionUnaria.h"

void ExpresionUnaria::SetExpr(Expresion* expr)
{
	this->expr = expr;
}

Expresion* ExpresionUnaria::GetExpr()
{
	return this->expr;
}