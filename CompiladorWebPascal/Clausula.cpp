#include "Clausula.h"


Clausula::Clausula(Clausula* siguiente, LimitesRango* limites)
{
	SetSiguiente(siguiente);
	SetLimites(limites);
}


Clausula::~Clausula(void)
{
	delete siguiente;
	delete lim;
}

void Clausula::SetLimites(LimitesRango* lim)
{
	this->lim = lim;
}

void Clausula::SetSiguiente(Clausula* siguiente)
{
	this->siguiente = siguiente;
}

LimitesRango* Clausula::GetLimites()
{
	return lim;
}

Clausula* Clausula::GetSiguiente()
{
	return siguiente;
}
