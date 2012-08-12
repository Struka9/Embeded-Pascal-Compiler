#pragma once
#include "ExprBinaria.h"
#include "ValorEntero.h"
#include "ValorReal.h"
#include "ValorCaracter.h"
class Suma :
	public ExprBinaria
{
public:
	Suma(Expresion* op1, Expresion* op2 );
	Tipo* validarSemantico();
	~Suma(void);
	Valor* interpretar();
};

