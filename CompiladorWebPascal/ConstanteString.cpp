#include "ConstanteString.h"

ConstanteString::ConstanteString(string sVal )
{
	SetString(sVal);
}

void ConstanteString::SetString(string val)
{
	this->sVal = val;
}

string ConstanteString::GetString()
{
	return sVal;
}

Tipo* ConstanteString::validarSemantico()
{
	return InformacionSemantica::GetInstance()->GetTablaTipos().find("STRING")->second;
}

Valor* ConstanteString::interpretar()
{
	return new ValorCadena(sVal);
}