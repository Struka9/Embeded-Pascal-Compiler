#pragma once
#include "ExprBinaria.h"
#include "ValorBooleano.h"
#include "ValorEntero.h"
#include "ValorReal.h"
#include "ValorCadena.h"
#include "ValorCaracter.h"
class ExprMayorIgual :
	public ExprBinaria
{
public:
	ExprMayorIgual(Expresion* izq,Expresion* der);
	Tipo* validarSemantico();
	Valor* interpretar();
	~ExprMayorIgual(void);
};

