#pragma once
#include "Valores.h"
#include "ListaValores.h"
#include "InformacionSemantica.h"
#include <string>
#include <map>
using namespace std;

class InformacionInterpretacion
{
private:
	map<string,ListaValores*> tabla_contexto;
	InformacionInterpretacion();
	static InformacionInterpretacion * instancia;
	string contexto;

public:
	void SetContexto(string contexto);
	Valor* clone(Valor* v);
	Valor* GetFromTablaValores(string nombre_var );
	void InsertarEnTablaValores(string nombre_var,Valor* valor );
	void InsertarValorEnContexto(string contexto,string id,Valor* v);
	static InformacionInterpretacion* GetInstance();
	void InicializarVariables(string nom_contexto,ListaVariables* vars);
	~InformacionInterpretacion();
};

