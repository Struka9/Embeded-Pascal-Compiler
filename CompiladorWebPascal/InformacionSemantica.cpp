#include "InformacionSemantica.h"

InformacionSemantica* InformacionSemantica::instancia = 0;

InformacionSemantica::InformacionSemantica(void)
{
	SetContexto("@GLOBAL");
	tablaTipos.insert( pair<string,Tipo*>("BOOLEAN",new Booleano() ) );
	tablaTipos.insert( pair<string,Tipo*>("INTEGER",new Entero() ) );
	tablaTipos.insert( pair<string,Tipo*>("CHAR",new Caracter() ) );
	tablaTipos.insert( pair<string,Tipo*>("STRING",new Cadena() ) );
	tablaTipos.insert( pair<string,Tipo*>("REAL",new Real() ) );
}


InformacionSemantica::~InformacionSemantica(void)
{
}

InformacionSemantica* InformacionSemantica::GetInstance()
{
	if ( InformacionSemantica::instancia == 0 )
		InformacionSemantica::instancia = new InformacionSemantica();

	return InformacionSemantica::instancia;
}

void InformacionSemantica::InsertarEnTablaTipos(string nombre_tipo,Tipo* t)
{
	map<string,Tipo*>::iterator it = tablaTipos.find(nombre_tipo);

	if ( it != tablaTipos.end() )
		throw SemanticException("El tipo " + nombre_tipo + " ya ha sido definido");

	tablaTipos.insert(pair<string,Tipo*>(nombre_tipo,t) );
}

map<string,Tipo*> InformacionSemantica::GetTablaTipos()
{
	return tablaTipos;
}

void InformacionSemantica::SetTablaSimbolos(ListaVariables* tabla)
{
	_tablasSimbolos.insert( pair<string,ListaVariables*>(contexto,tabla) );
}


void InformacionSemantica::SetContexto(string str)
{
	std::transform(str.begin(), str.end(), str.begin(), 
               (int(*)(int)) toupper);

	this->contexto = str;

}

string InformacionSemantica::GetContexto()
{
	return contexto;
}

Tipo* InformacionSemantica::GetFromTablaSimbolos(string id)
{
	//TODO: Seguir un orden cuando no es contexto global params->locales->globales
	ListaVariables* vars = NULL;
	if ( contexto.compare("@GLOBAL") == 0 )
	{
		map<string,ListaVariables*>::iterator it = _tablasSimbolos.find(contexto);
		if ( it == _tablasSimbolos.end() )
			return NULL;

		vars = it->second;
		return vars->get(id);
	}
	else 
	{
		map<string,ListaVariables*>::iterator it = _tablasSimbolos.find(contexto);

		vars = it->second;

		Tipo* t = vars->get(id);

		if ( t == NULL )
		{
			vars = _tablasSimbolos.find("@GLOBAL")->second;

			return vars->get(id);
		}
		return t;
	}
	
}

void InformacionSemantica::InsertarVarEnContexto(string contexto,string id,Tipo* t)
{
	map<string,ListaVariables*>::iterator it = _tablasSimbolos.find(contexto);
	
	if ( it == _tablasSimbolos.end() )
		return;

	ListaVariables* lista = it->second;

	lista->insert(id,t);
	_tablasSimbolos.insert(pair<string,ListaVariables*>(contexto,lista) );
	
}

Tipo* InformacionSemantica::GetFromTablaTipos(string custom_type)
{
	map<string,Tipo*>::iterator it = tablaTipos.find(custom_type);

	if ( it == tablaTipos.end() )
		return NULL;

	return it->second;
}

void InformacionSemantica::InsertarEnTablaDeFunciones(string nombre_funcion,DeclaracionFuncion* func)
{
	tablaFunciones.insert( pair<string,DeclaracionFuncion*>(nombre_funcion,func) );
}

DeclaracionFuncion* InformacionSemantica::GetFromTablaFunciones(string nombre_funcion)
{
	map<string,DeclaracionFuncion*>::iterator it = tablaFunciones.find(nombre_funcion);

	if ( it == tablaFunciones.end() )
		return NULL;

	return it->second;
}

ListaVariables* InformacionSemantica::GetTablaSimbolos()
{
	map<string,ListaVariables*>::iterator it = _tablasSimbolos.find( contexto );

	if ( it != _tablasSimbolos.end() )
		return it->second;
	else
		return (ListaVariables*)0;
}