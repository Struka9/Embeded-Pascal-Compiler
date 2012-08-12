#pragma once
#include "Valor.h"
class ValorEntero :
	public Valor
{
private:
	int valor;

public:
	Valor* clone();
	ValorEntero();
	ValorEntero(int val);
	int GetVal();
	void SetVal(int num);
	tipo_valor GetTipoValor();
	~ValorEntero(void);
};

