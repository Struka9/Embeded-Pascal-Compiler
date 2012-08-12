#pragma once
#include "ValorEntero.h"
#include "ConstanteLiteral.h"
class ConstanteEntera :
	public ConstanteLiteral
{
	int valor;
public:
	Tipo* validarSemantico();
	ConstanteEntera(int valor);
	void SetValor(int num);
	int GetValor();
	Valor* interpretar();
};

