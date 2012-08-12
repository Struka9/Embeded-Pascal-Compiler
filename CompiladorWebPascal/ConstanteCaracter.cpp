#include "ConstanteCaracter.h"


ConstanteCaracter::ConstanteCaracter(string c)
{
	SetVal(c);
}


ConstanteCaracter::~ConstanteCaracter(void)
{
}

void ConstanteCaracter::SetVal(string c)
{
	this->cVal = c;
}

string ConstanteCaracter::GetVal()
{
	return cVal;
}

Tipo* ConstanteCaracter::validarSemantico()
{
	return InformacionSemantica::GetInstance()->GetTablaTipos().find("CHAR")->second;
}

Valor* ConstanteCaracter::interpretar()
{
	return new ValorCaracter(cVal);
}