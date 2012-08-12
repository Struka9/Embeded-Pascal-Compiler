#include "ValorReal.h"

ValorReal::ValorReal()
{
	SetVal(0.0);
}

ValorReal::ValorReal(double val)
{
	SetVal(val);
}


ValorReal::~ValorReal(void)
{
}

Valor* ValorReal::clone()
{
	return new ValorReal(val);
}

void ValorReal::SetVal(double val)
{
	this->val = val;
}

double ValorReal::GetVal()
{
	return val;
}

tipo_valor ValorReal::GetTipoValor()
{
	return real;
}