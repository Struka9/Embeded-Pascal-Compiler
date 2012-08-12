#pragma once

#include "ConstanteLiteral.h"
#include "ValorCadena.h"
#include <string>
using namespace std;

class ConstanteString: public ConstanteLiteral
{
private:
	string sVal;

public:
	Tipo* validarSemantico();
	ConstanteString(string sVal);
	void SetString(string val);
	string GetString();
	Valor* interpretar();
};