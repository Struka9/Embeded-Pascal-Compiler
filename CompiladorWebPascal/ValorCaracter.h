#pragma once
#include "Valor.h"
#include <string>
using namespace std;
class ValorCaracter :
	public Valor
{
private:
	string val;
public:
	Valor* clone();
	ValorCaracter();
	ValorCaracter(string val);
	~ValorCaracter(void);
	tipo_valor GetTipoValor();
	void SetVal(string val);
	string GetVal();
};

