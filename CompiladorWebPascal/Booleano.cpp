#include "Booleano.h"


Booleano::Booleano(void)
{
}


Booleano::~Booleano(void)
{
}

bool Booleano::EsEquivalente(Tipo* t)
{
	return t->GetTipo() == t_boolean||t->GetTipo()== t_entero;
}

tipo_dato Booleano::GetTipo()
{
	return t_boolean;
}