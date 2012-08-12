#pragma once
#include "SemanticException.h"
#include "Tipo.h"
#include <string>
#include <map>
#include <list>
using namespace std;
class ListaVariables
{
public:
	ListaVariables(void);
	~ListaVariables(void);
	void insert(string key,Tipo* value);
	Tipo* get(string key);
	list<string> GetNombreCampos();
private:
	list<string> campos;
	map<string,Tipo*> variables;
};

