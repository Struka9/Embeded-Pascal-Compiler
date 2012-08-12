#pragma once
#include "ValorReal.h"
#include "ValorEntero.h"
#include "ExpresionUnaria.h"
class RestaUnaria :
	public ExpresionUnaria
{
public:
	RestaUnaria(Expresion* expr);
	~RestaUnaria(void);
	Tipo* validarSemantico();
	Valor* interpretar();
};

