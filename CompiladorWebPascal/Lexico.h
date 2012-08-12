#pragma once
#include "LectorArchivo.h"
#include "LexicalException.h"
#include "Token.h"
#include "Util.h"
#include <string>
#include <map>
using namespace std;

class Lexico
{
private:
	bool modo_html;
	unsigned int linea_actual;
	void MapInit();
	map<string,Token> palabras_reservadas;
	LectorArchivo *codigo_fuente;
	Token ObtenerSiguienteTokenPascal();
	Token ObtenerSiguienteTokenHTML();
public:
	unsigned int GetLineaActual();
	Lexico(string nombre_archivo);
	Token ObtenerSiguienteToken();
	~Lexico(void);
};

