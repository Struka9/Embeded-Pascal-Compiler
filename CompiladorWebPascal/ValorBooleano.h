#pragma once
#include "valor.h"
class ValorBooleano :
	public Valor
{
private:
	bool val;
public:
	Valor* clone();
	ValorBooleano();
	ValorBooleano(bool valor);
	~ValorBooleano(void);
	tipo_valor GetTipoValor();
	void SetVal(bool boolean);
	bool GetVal();
};

