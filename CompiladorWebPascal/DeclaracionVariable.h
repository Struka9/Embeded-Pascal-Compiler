#pragma once
#include "Tipo.h"
#include "Registro.h"
#include "Arreglo.h"
#include "InformacionInterpretacion.h"
#include "Valores.h"
#include <list>
#include <string>
using namespace std;
class DeclaracionVariable
{
private:
	list<string> ids;
	Tipo* tipo;

public:
	DeclaracionVariable(list<string>ids,Tipo* t);
	~DeclaracionVariable(void);
	void SetIds(list<string> ids);
	void SetTipo(Tipo* t);
	Tipo* GetTipo();
	list<string> GetIds();
};

