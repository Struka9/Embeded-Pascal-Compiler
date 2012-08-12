#pragma once
#include "ExprBinaria.h"
#include "ValorBooleano.h"
class OrBinario :
	public ExprBinaria
{
public:
	OrBinario(Expresion* op1,Expresion* op2);
	~OrBinario(void);
	Tipo* validarSemantico();
	Valor* interpretar();
};

