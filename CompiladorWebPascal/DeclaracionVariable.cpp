#include "DeclaracionVariable.h"


DeclaracionVariable::DeclaracionVariable(list<string>ids,Tipo* t)
{
	SetIds(ids);
	SetTipo(t);
}


DeclaracionVariable::~DeclaracionVariable(void)
{
	delete tipo;
}

void DeclaracionVariable::SetIds(list<string>ids)
{
	this->ids = ids;
}

void DeclaracionVariable::SetTipo(Tipo* t)
{
	this->tipo = t;
}

list<string> DeclaracionVariable::GetIds()
{
	return ids;
}

Tipo* DeclaracionVariable::GetTipo()
{
	return tipo;
}
