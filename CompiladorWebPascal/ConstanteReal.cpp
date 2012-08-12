#include "ConstanteReal.h"


ConstanteReal::ConstanteReal(double val)
{
	SetValor(val);
}

void ConstanteReal::SetValor(double val)
{
	this->valor = val;
}

double ConstanteReal::GetValor()
{
	return valor;
}

Tipo* ConstanteReal::validarSemantico()
{
	return InformacionSemantica::GetInstance()->GetTablaTipos().find("REAL")->second;
}

Valor* ConstanteReal::interpretar()
{
	return new ValorReal(valor);
}