#pragma once
#include "ExprBinaria.h"
#include "ValorEntero.h"
#include "ValorReal.h"
class Multiplicacion :
	public ExprBinaria
{
public:
	Tipo* validarSemantico();
	Multiplicacion(Expresion* op1, Expresion* op2);
	Valor* interpretar();
	~Multiplicacion(void);
};

