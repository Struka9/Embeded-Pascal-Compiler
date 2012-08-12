#pragma once
#include "valor.h"
#include <string>
using namespace std;

class ValorCadena :
	public Valor
{
private:
	string valor;
public:
	Valor* clone();
	ValorCadena();
	ValorCadena(string valor);
	~ValorCadena(void);
	string GetValor();
	void SetValor(string str);
	tipo_valor GetTipoValor();
};

