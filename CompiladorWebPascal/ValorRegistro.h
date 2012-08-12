#pragma once
#include "Registro.h"
#include "Valores.h"
#include <map>
#include <string>
using namespace std;

class ValorRegistro :
	public Valor
{
	map<string,Valor*>valores_campos;

public:
	Valor* clone();
	Valor* GetVal(string campo);
	void SetVal(string campo,Valor* val);
	ValorRegistro();
	ValorRegistro(Registro* t_reg);
	ValorRegistro(map<string,Valor*>campos);
	tipo_valor GetTipoValor();
	~ValorRegistro(void);
};

