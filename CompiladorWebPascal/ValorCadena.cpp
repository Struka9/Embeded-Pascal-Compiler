#include "ValorCadena.h"

ValorCadena::ValorCadena()
{
	SetValor("");
}

ValorCadena::ValorCadena(string valor)
{
	SetValor(valor);
}


ValorCadena::~ValorCadena(void)
{
}

Valor* ValorCadena::clone()
{
	return new ValorCadena(valor);
}

string ValorCadena::GetValor()
{
	return valor;
}

void ValorCadena::SetValor(string valor)
{
	this->valor = valor;
}

tipo_valor ValorCadena::GetTipoValor()
{
	return cadena;
}

