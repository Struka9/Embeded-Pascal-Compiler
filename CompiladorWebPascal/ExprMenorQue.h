#pragma once
#include "ExprBinaria.h"
#include "ValorBooleano.h"
#include "ValorEntero.h"
#include "ValorReal.h"
#include "ValorCadena.h"
#include "ValorCaracter.h"

class ExprMenorQue:
	public ExprBinaria
{
public:
	ExprMenorQue(Expresion* izq, Expresion* der);
	Tipo* validarSemantico();
	Valor* interpretar();
	~ExprMenorQue(void);
};

