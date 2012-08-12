#include "ListaVariables.h"


ListaVariables::ListaVariables(void)
{
}


ListaVariables::~ListaVariables(void)
{
}

void ListaVariables::insert(string key,Tipo* value)
{
	//TODO: Verificar
	map<string,Tipo*>::iterator it = variables.find(key);
	if ( it != variables.end() )
		throw SemanticException("La variable "+key+" ya ha sido definida");
	campos.push_back(key);
	variables.insert(pair<string,Tipo*>(key,value) );	
}

Tipo* ListaVariables::get(string key)
{
	
	map<string,Tipo*>::iterator it = variables.find(key);
	if ( it == variables.end() )
		return 0;

	return it->second;
}

list<string> ListaVariables::GetNombreCampos()
{
	return this->campos;
}