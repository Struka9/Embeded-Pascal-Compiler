#pragma once
#include "ExprBinaria.h"
#include "ValorBooleano.h"
#include "ValorEntero.h"
#include "ValorReal.h"
#include "ValorCadena.h"
#include "ValorCaracter.h"
class ExprMenorIgual :
	public ExprBinaria
{
public:
	ExprMenorIgual(Expresion* izq,Expresion* der);
	Tipo* validarSemantico();
	Valor* interpretar();
	~ExprMenorIgual(void);
};

