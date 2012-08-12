#pragma once
#include "Tipo.h"
#include <string>
using namespace std;

class Parametro
{
private:
	bool esPorReferencia;
	string nom_parametro;
	Tipo* tipo;

public:
	Parametro(string nombre,bool esReferencia,Tipo* tipo);
	~Parametro();

	void SetNombre(string str);
	void SetReferencia(bool esPorReferencia);
	void SetTipo(Tipo* tipo);

	string GetNombre();
	bool EsPorReferencia();
	Tipo* GetTipo();

	bool EsIgual(Parametro* p);
};