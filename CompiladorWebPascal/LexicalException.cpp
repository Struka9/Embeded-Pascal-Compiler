#include "LexicalException.h"


LexicalException::LexicalException(int linea, string mensaje):runtime_error( mensaje )
{
	this->mensaje = mensaje;
	this->linea = linea;
}

LexicalException::~LexicalException(void)
{
}

int LexicalException::GetLinea()
{
	return linea;
}
