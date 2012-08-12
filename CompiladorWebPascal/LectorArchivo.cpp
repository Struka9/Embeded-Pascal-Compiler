#include "LectorArchivo.h"


LectorArchivo::LectorArchivo(string nombre_archivo)
{
	this->nombre = nombre_archivo;	
}

bool LectorArchivo::ObtenerContenido()
{
	ifstream archivo;
	archivo.open( nombre.c_str() );

	if ( archivo.is_open() )
	{
		while( archivo.good() )
		{
			string linea;
			getline(archivo,linea);
			contenido += linea + "\n";
		}
		archivo.close();
	}
	else
		return false;

	cursor = 0;
	return true;
}

char LectorArchivo::LeerCaracter()
{
	if ( cursor == contenido.size() )
		return EOF;

	char ret = contenido.at( cursor );
	return ret;
}

void LectorArchivo::Avanzar(int n)
{
	cursor+=n;
}

void LectorArchivo::Retroceder(int n)
{
	cursor-=n;
}

LectorArchivo::~LectorArchivo(void)
{
}
