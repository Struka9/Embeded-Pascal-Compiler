#include "SemanticException.h"


SemanticException::SemanticException(string mensaje):runtime_error(mensaje.c_str() )
{
	this->msj ="Error semantico: " +  mensaje ;
}


SemanticException::~SemanticException(void)
{
}

string SemanticException::GetMensaje()
{
	return msj;
}