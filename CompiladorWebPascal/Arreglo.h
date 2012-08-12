#pragma once
#include "Tipo.h"
#include "LimitesRango.h"
#include <list>
using namespace std;

class Arreglo :
	public Tipo
{
private:
	list<LimitesRango*> lim;
	Tipo* of;

public:
	Arreglo(list<LimitesRango*> limites,Tipo* of);
	~Arreglo(void);
	int GetSizeOfIndex(int index);
	bool EsEquivalente(Tipo* t);
	tipo_dato GetTipo();

	void SetLimites(list<LimitesRango*> lim);
	void SetOf(Tipo* t);
	int mapeo(int n_lim,int index);
	Tipo* GetOf();
	list<LimitesRango*> GetLim();
};

