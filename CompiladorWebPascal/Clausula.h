#pragma once
#include "LimitesRango.h"
class Clausula
{
private:
	Clausula* siguiente;
	LimitesRango* lim;
public:
	Clausula(Clausula* siguiente, LimitesRango* limites);
	~Clausula(void);

	void SetSiguiente(Clausula* siguiente);
	void SetLimites(LimitesRango* limites);

	Clausula* GetSiguiente();
	LimitesRango* GetLimites();
};

