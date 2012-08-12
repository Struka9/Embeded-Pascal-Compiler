#include "ConstanteEntera.h"


ConstanteEntera::ConstanteEntera(int valor)
{
	SetValor(valor);
}

void ConstanteEntera::SetValor(int num)
{
	valor = num;
}

int ConstanteEntera::GetValor()
{
	return valor;
}

Tipo* ConstanteEntera::validarSemantico()
{
	return InformacionSemantica::GetInstance()->GetTablaTipos().find("INTEGER")->second;
}

Valor* ConstanteEntera::interpretar()
{
	return new ValorEntero(valor);
}