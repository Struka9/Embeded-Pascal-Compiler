#pragma once
#include "ValorEntero.h"
#include "ExprBinaria.h"
class Modulo :
	public ExprBinaria
{
public:
	Tipo* validarSemantico();
	Modulo(Expresion* op1,Expresion* op2);
	Valor* interpretar();
	~Modulo(void);
};

