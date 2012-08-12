#include "ValorBooleano.h"

ValorBooleano::ValorBooleano()
{
	SetVal(false);
}

ValorBooleano::ValorBooleano(bool val)
{
	SetVal(val);
}


ValorBooleano::~ValorBooleano(void)
{
}

Valor* ValorBooleano::clone()
{
	return new ValorBooleano(val);
}

void ValorBooleano::SetVal(bool val)
{
	this->val = val;
}

bool ValorBooleano::GetVal()
{
	return val;
}

tipo_valor ValorBooleano::GetTipoValor()
{
	return boolean;
}


