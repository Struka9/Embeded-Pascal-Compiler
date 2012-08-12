#pragma once
#include "Tipo.h"
class Entero :
	public Tipo
{
public:
	Entero();
	bool EsEquivalente(Tipo* t);
	~Entero(void);
	tipo_dato GetTipo();
};

