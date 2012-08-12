#pragma once
#include "Tipo.h"
class Caracter :
	public Tipo
{
public:
	bool EsEquivalente(Tipo* t);
	tipo_dato GetTipo();
	Caracter(void);
	~Caracter(void);
};

