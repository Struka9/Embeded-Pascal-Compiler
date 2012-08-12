#include "Real.h"


Real::Real(void)
{
}


Real::~Real(void)
{
}

bool Real::EsEquivalente(Tipo* t)
{
	return ( t->GetTipo() == t_entero || t->GetTipo() == t_real );
}

tipo_dato Real::GetTipo()
{
	return t_real;
}