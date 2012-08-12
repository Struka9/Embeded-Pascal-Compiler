#include "Sentencia.h"

void Sentencia::SetSiguiente( Sentencia* siguiente )
{
	this->siguiente = siguiente;
}

Sentencia* Sentencia::GetSiguiente()
{
	return siguiente;
}
