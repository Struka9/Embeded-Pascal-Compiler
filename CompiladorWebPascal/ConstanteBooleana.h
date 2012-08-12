#pragma once
#include "ConstanteLiteral.h"
#include "ValorBooleano.h"
class ConstanteBooleana :
	public ConstanteLiteral
{
private:
	bool bVal;
public:
	ConstanteBooleana(bool val);
	~ConstanteBooleana(void);
	bool GetVal();
	void SetVal(bool val);
	Tipo* validarSemantico();
	Valor* interpretar();
};

