#pragma once
#include "Valor.h"
#include <string>
#include <map>
using namespace std;
class ListaValores
{
private:
	map<string,Valor*> valores;
public:
	ListaValores();
	~ListaValores(void);
	void Insertar(string id,Valor* val);
	Valor* ObtenerValor(string id);
};

