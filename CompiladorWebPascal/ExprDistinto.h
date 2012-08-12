#pragma once
#include "ExprBinaria.h"
#include "ValorBooleano.h"
#include "ValorEntero.h"
#include "ValorReal.h"
#include "ValorCadena.h"
#include "ValorCaracter.h"

class ExprDistinto :
	public ExprBinaria
{
public:
	ExprDistinto(Expresion* izq, Expresion* der);
	Tipo* validarSemantico();
	~ExprDistinto(void);
	Valor* interpretar();
};

