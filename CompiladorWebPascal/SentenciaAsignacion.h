#pragma once
#include "Sentencia.h"
#include "Expresion.h"
#include "Identificador.h"
class SentenciaAsignacion :
	public Sentencia
{
private:
	Identificador* id;
	Expresion* expr;
	void validarSemantica();
	void Interpretar();

public:
	SentenciaAsignacion(Identificador* id,Expresion* expr);
	~SentenciaAsignacion(void);
	void SetId(Identificador* id);
	void SetExpresion(Expresion* expr);
	Expresion* GetExpresion();
	Identificador* GetId();
	
};

