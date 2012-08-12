#pragma once
#include "Expresion.h"
#include "Qualifier.h"
#include "Indexacion.h"
#include "Referencia.h"
#include "InformacionInterpretacion.h"
#include <list>
#include <string>
using namespace std;

class Tipo;
class Identificador:
	public Expresion
{
private:
	string id;
	list<Qualifier*> qualifiers;

public:
	void GuardarEnTablaValores(Valor* val);
	Identificador(string nombre,list<Qualifier*>qualifiers);
	void SetId(string nombre);
	string GetId();
	void SetQualifiers(list<Qualifier*> qualifiers);
	list<Qualifier*> GetQualifiers();
	Tipo* validarSemantico();
	Valor* interpretar();
};