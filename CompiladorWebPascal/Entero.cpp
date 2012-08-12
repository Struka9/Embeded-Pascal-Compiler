#include "Entero.h"


Entero::Entero()
{
}


Entero::~Entero(void)
{
}

bool Entero::EsEquivalente(Tipo* t)
{
	return ( t->GetTipo() == t_entero ||
		t->GetTipo() == t_real );	
}

tipo_dato Entero::GetTipo()
{
	return t_entero;
}