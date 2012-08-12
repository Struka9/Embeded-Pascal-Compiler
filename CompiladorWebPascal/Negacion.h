#pragma once
#include "ExpresionUnaria.h"
#include "ValorBooleano.h"
class Negacion :
	public ExpresionUnaria
{
public:
	Tipo* validarSemantico();
	Negacion(Expresion* expr);
	~Negacion(void);
	Valor* interpretar();
};

