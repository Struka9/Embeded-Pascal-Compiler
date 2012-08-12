#include "Referencia.h"


Referencia::Referencia(string nom_campo)
{
	SetCampo(nom_campo);
}


Referencia::~Referencia(void)
{
}

void Referencia::SetCampo(string str)
{
	this->nom_campo = str;
}

string Referencia::GetCampo()
{
	return nom_campo;
}

tipo_qualifier Referencia::GetTipo()
{
	return qt_campo;
}