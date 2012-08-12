#include "ConstanteBooleana.h"


ConstanteBooleana::ConstanteBooleana(bool val)
{
	SetVal(val);
}


ConstanteBooleana::~ConstanteBooleana(void)
{
}

void ConstanteBooleana::SetVal(bool val)
{
	this->bVal = val;
}

bool ConstanteBooleana::GetVal()
{
	return bVal;
}

Tipo* ConstanteBooleana::validarSemantico()
{
	return InformacionSemantica::GetInstance()->GetTablaTipos().find("BOOLEAN")->second;
}

Valor* ConstanteBooleana::interpretar()
{
	return new ValorBooleano(bVal);
}