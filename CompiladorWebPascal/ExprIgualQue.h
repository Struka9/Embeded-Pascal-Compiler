#pragma once
#include "ExprBinaria.h"
#include "ValorBooleano.h"
#include "ValorEntero.h"
#include "ValorReal.h"
#include "ValorCadena.h"
#include "ValorCaracter.h"
class ExprIgualQue: public ExprBinaria
{
public:
	ExprIgualQue(Expresion* izq,Expresion* der);
	Tipo* validarSemantico();
	Valor* interpretar();
	~ExprIgualQue(void);
};

