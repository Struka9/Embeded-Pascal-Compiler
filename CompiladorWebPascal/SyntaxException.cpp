#include "SyntaxException.h"


SyntaxException::SyntaxException(string mensaje,int linea): runtime_error("")
{
	this->linea = linea;
	this->mensaje = "Error Sintactico: " + mensaje+ ",en la linea " + std::to_string((_ULonglong)linea); 
}


SyntaxException::~SyntaxException(void)
{
}

string SyntaxException::GetMensaje()
{
	return mensaje;
}