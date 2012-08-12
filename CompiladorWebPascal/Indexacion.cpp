#include "Indexacion.h"


Indexacion::Indexacion(list<Expresion*>listaIndices)
{
	this->listaIndices = listaIndices;
}


Indexacion::~Indexacion(void)
{
}

void Indexacion::SetIndices(list<Expresion*> lista)
{
	this->listaIndices = lista;
}

list<Expresion*> Indexacion::GetIndices()
{
	list<Expresion*> l_nueva = listaIndices;
	return l_nueva;
}

tipo_qualifier Indexacion::GetTipo()
{
	return qt_index;
}