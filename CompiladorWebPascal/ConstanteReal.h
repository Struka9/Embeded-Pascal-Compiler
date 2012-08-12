#pragma once
#include "ConstanteLiteral.h"
#include "ValorReal.h"
class ConstanteReal :
	public ConstanteLiteral
{
private:
	double valor;

public:
	Tipo* validarSemantico();
	ConstanteReal(double val);
	void SetValor( double val );
	double GetValor();
	Valor* interpretar();
};

