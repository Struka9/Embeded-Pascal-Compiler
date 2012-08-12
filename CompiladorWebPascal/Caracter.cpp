#include "Caracter.h"


Caracter::Caracter(void)
{
}


Caracter::~Caracter(void)
{
}

bool Caracter::EsEquivalente(Tipo* t)
{
	return t->GetTipo()==t_caracter || t->GetTipo() == t_cadena;
}

tipo_dato Caracter::GetTipo()
{
	return t_caracter;
}