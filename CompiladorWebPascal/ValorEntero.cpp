#include "ValorEntero.h"

ValorEntero::ValorEntero()
{
	SetVal(0);
}

ValorEntero::ValorEntero(int val)
{
	SetVal(val);
}


ValorEntero::~ValorEntero(void)
{
}

Valor* ValorEntero::clone()
{
	return new ValorEntero(valor);
}

int ValorEntero::GetVal()
{
	return valor;
}

void ValorEntero::SetVal(int num)
{
	this->valor = num;
}

tipo_valor ValorEntero::GetTipoValor()
{
	return entero;
}