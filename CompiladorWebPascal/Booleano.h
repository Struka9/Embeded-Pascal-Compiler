#pragma once
#include "Tipo.h"
class Booleano :
	public Tipo
{
public:
	Booleano();
	~Booleano(void);
	bool EsEquivalente(Tipo* t);
	tipo_dato GetTipo();
};

