#pragma once
#include "ExpresionUnaria.h"
class SumaUnaria :
	public ExpresionUnaria
{
public:
	SumaUnaria(Expresion* expr);
	Tipo* validarSemantico();
	Valor* interpretar();
	~SumaUnaria(void);
};

