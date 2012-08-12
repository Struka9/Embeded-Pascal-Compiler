#pragma once
#include "Qualifier.h"
#include "Expresion.h"
#include <list>
using namespace std;

class Indexacion :
	public Qualifier
{
private:
	list<Expresion*> listaIndices;

public:
	Indexacion(list<Expresion*>listaIndices);
	~Indexacion(void);
	void SetIndices(list<Expresion*> lista);
	list<Expresion*> GetIndices();
	tipo_qualifier GetTipo();
};

