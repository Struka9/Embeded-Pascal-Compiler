#pragma once
#include "ConstanteLiteral.h"
#include "ValorCaracter.h"
#include <string>
using namespace std;
class ConstanteCaracter :
	public ConstanteLiteral
{
private:
	string cVal;
public:
	ConstanteCaracter(string c);
	void SetVal(string c);
	string GetVal();
	Tipo* validarSemantico();
	Valor* interpretar();
	~ConstanteCaracter(void);
};

