#include "LimitesRango.h"


LimitesRango::LimitesRango(int inferior,int superior)
{
	SetInferior(inferior);
	SetSuperior(superior);
}


LimitesRango::~LimitesRango(void)
{
}
 

void LimitesRango::SetInferior(int inf)
{
	inferior = inf;
}

void LimitesRango::SetSuperior(int sup)
{
	superior = sup;
}

int LimitesRango::GetInferior()
{
	return inferior;
}

int LimitesRango::GetSuperior()
{
	return superior;
}

int LimitesRango::GetCant()
{
	return superior-inferior;
}