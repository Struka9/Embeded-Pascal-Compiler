#pragma once
#include <algorithm>
#include <cctype>
#include "Tipo.h"
#include "Entero.h"
#include "Real.h"
#include "Arreglo.h"
#include "Cadena.h"
#include "Caracter.h"
#include "Booleano.h"
#include "Registro.h"
#include "ListaVariables.h"
#include "DeclaracionFuncion.h"
#include "SemanticException.h"
#include <map>
#include <string>
using namespace std;

class DeclaracionFuncion;
class InformacionSemantica
{
private:
	string contexto;
	static InformacionSemantica* instancia;
	
	map<string,Tipo*> tablaTipos;
	map<string,ListaVariables*> _tablasSimbolos;
	map<string,DeclaracionFuncion*> tablaFunciones;
	InformacionSemantica();

public:
	void InsertarEnTablaDeFunciones(string nom_func,DeclaracionFuncion* fun);
	DeclaracionFuncion* GetFromTablaFunciones(string nom_func);

	void SetContexto( string str);
	string GetContexto();

	void SetTablaSimbolos(ListaVariables* tabla);
	ListaVariables* GetTablaSimbolos();
	Tipo* GetFromTablaSimbolos(string id);
	Tipo* GetFromTablaTipos(string custom_type);
	map<string,Tipo*> GetTablaTipos();

	void InsertarVarEnContexto(string context,string id, Tipo* t);
	void InsertarEnTablaTipos(string nombre,Tipo* t);

	static InformacionSemantica* GetInstance();
	~InformacionSemantica(void);
};

