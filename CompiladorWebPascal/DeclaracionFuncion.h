#pragma once
#include "Tipo.h"
#include "Parametro.h"
#include "ListaVariables.h"
#include "InformacionSemantica.h"
#include <list>
#include "Sentencia.h"
#include <string>
#include <map>
using namespace std;
class DeclaracionFuncion
{
	string nom_func;
	list<Parametro*> lista_parametros;
	Sentencia* cuerpo_funcion;
	Tipo* tipo;
	
public:
	DeclaracionFuncion(string nombre_funcion,list<Parametro*> lista_parametros,
		Sentencia* cuerpo_func,Tipo* tipo);
	~DeclaracionFuncion(void);
	
	void SetNombreFuncion(string str);
	void SetParametros(list<Parametro*> lista_parametros);
	void SetCuerpoFunc(Sentencia* stmt);
	void SetTipo(Tipo* t);

	string GetNombre();
	Tipo* GetTipo();
	list<Parametro*> GetParametros();
	Sentencia* GetCuerpoFuncion();

	void ValidarSemantica();
};

