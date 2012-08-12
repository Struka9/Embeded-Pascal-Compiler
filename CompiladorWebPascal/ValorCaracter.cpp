#include "ValorCaracter.h"

ValorCaracter::ValorCaracter()
{
	SetVal("");
}

ValorCaracter::ValorCaracter(string val)
{
	SetVal(val);
}


ValorCaracter::~ValorCaracter(void)
{
}

Valor* ValorCaracter::clone()
{
	return new ValorCaracter(val);
}

tipo_valor ValorCaracter::GetTipoValor()
{
	return caracter;
}

void ValorCaracter::SetVal(string val)
{
	this->val = val;
}

string ValorCaracter::GetVal()
{
	return val;
}