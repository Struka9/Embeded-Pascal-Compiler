#include "ListaValores.h"


ListaValores::ListaValores()
{
}


ListaValores::~ListaValores(void)
{
}

void ListaValores::Insertar(string id,Valor* val)
{
	valores[id] = val;
}

Valor* ListaValores::ObtenerValor(string id)
{
	map<string,Valor*>::iterator it = valores.find(id);

	if ( it == valores.end() )
		return NULL;

	return it->second;
}