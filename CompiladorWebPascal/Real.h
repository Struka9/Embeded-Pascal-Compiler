#pragma once
#include "Tipo.h"
class Real :
	public Tipo
{
public:
	Real();
	~Real(void);
	tipo_dato GetTipo();
	bool EsEquivalente(Tipo* t);
};

