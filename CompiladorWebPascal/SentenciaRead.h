#pragma once
#include "sentencia.h"
#include "Valores.h"
#include "Identificador.h"
#include <iostream>
#include <string>
using namespace std;
class SentenciaRead :
	public Sentencia
{
private:
	Identificador* id;
	void validarSemantica();
	void Interpretar();
public:
	SentenciaRead(Identificador* id);
	void SetId(Identificador* id);
	Identificador* GetId();
	~SentenciaRead();
};

