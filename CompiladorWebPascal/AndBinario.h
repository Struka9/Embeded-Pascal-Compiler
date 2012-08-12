#pragma once
#include "ExprBinaria.h"
#include "ValorBooleano.h"
class AndBinario :
	public ExprBinaria
{
public:
	Tipo* validarSemantico();
	AndBinario(Expresion* op1,Expresion* op2);
	Valor* interpretar();
	~AndBinario(void);
};

