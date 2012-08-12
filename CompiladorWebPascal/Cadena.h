#pragma once
#include "Tipo.h"
class Cadena :
	public Tipo
{
public:
	Cadena(void);
	~Cadena(void);
	bool EsEquivalente(Tipo* t);
	tipo_dato GetTipo();
};

