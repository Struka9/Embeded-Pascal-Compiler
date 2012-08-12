#include "ListaSentencias.h"


ListaSentencias::ListaSentencias(Sentencia* lista_stmt)
{
	SetSiguiente(0);
	SetListaSentencias(lista_stmt);
}


ListaSentencias::~ListaSentencias(void)
{
	delete lista_stmt;
	delete siguiente;
}

void ListaSentencias::SetListaSentencias(Sentencia* lista_stmt)
{
	this->lista_stmt = lista_stmt;
}

Sentencia* ListaSentencias::GetListaSentencias()
{
	return lista_stmt;
}

void ListaSentencias::validarSemantica()
{
	lista_stmt->validacionSemantica();
}

void ListaSentencias::Interpretar()
{
	lista_stmt->Interpretacion();
}