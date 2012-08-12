#pragma once
#include "ValorEntero.h"
#include "ValorReal.h"
#include "ValorCaracter.h"
#include "ExprBinaria.h"
class Resta :
	public ExprBinaria
{
public:
	Resta(Expresion* op1,Expresion* op2);
	~Resta(void);
	Tipo* validarSemantico();
	Valor* interpretar();
};

