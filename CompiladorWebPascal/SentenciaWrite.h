#pragma once
#include "DefNodosExpresion.h"
#include "sentencia.h"
#include "Valores.h"
#include <iostream>
using namespace std;
class SentenciaWrite :
	public Sentencia
{
private:
	Expresion* expr;
	void validarSemantica();
	void Interpretar();
public:
	SentenciaWrite(Expresion* expr);
	void SetExpresion(Expresion* expr);
	Expresion* GetExpresion();
	~SentenciaWrite(void);
};

