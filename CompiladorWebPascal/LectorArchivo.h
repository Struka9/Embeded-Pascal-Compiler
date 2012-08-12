#pragma once
#include <fstream>
#include <string>
#include <iostream>
using namespace std;
class LectorArchivo
{
private:
	string nombre;
	string contenido;
	size_t cursor;

public:
	LectorArchivo(string nombre_archivo);
	bool ObtenerContenido();
	char LeerCaracter();
	void Avanzar(int n=1);
	void Retroceder(int n=1);
	~LectorArchivo(void);
};

