#pragma once
#include "ExprBinaria.h"
#include "ValorBooleano.h"
#include "ValorEntero.h"
#include "ValorReal.h"
#include "ValorCadena.h"
#include "ValorCaracter.h"
class ExprMayorQue: public ExprBinaria
{
public:
	ExprMayorQue(Expresion* izq,Expresion* der);
	Tipo* validarSemantico();
	Valor* interpretar();
	~ExprMayorQue(void);
};

