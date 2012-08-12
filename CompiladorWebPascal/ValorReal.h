#pragma once
#include "valor.h"
class ValorReal :
	public Valor
{
private:
	double val;

public:
	Valor* clone();
	ValorReal();
	ValorReal(double val);
	~ValorReal(void);
	tipo_valor GetTipoValor();
	void SetVal(double val);
	double GetVal();
};

