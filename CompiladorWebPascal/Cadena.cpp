#include "Cadena.h"


Cadena::Cadena(void)
{
}


Cadena::~Cadena(void)
{
}

bool Cadena::EsEquivalente(Tipo* t)
{
	return t->GetTipo()==t_cadena || t->GetTipo()==t_caracter;
}

tipo_dato Cadena::GetTipo()
{
	return t_cadena;
}