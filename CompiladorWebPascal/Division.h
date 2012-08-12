#pragma once
#include "ExprBinaria.h"
#include "ValorEntero.h"
#include "ValorReal.h"
class Division :
	public ExprBinaria
{
public:
	Division(Expresion* op1,Expresion* op2);
	~Division(void);
	Tipo* validarSemantico();
	Valor* interpretar();
};

