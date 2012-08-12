#pragma once
#include "Sentencia.h"
#include "Expresion.h"
#include "ClausulaCase.h"
#include "ValorEntero.h"
#include "ValorCaracter.h"
#include <list>
using namespace std;

class SentenciaCase :
	public Sentencia
{
private:
	Expresion* evaluacion;
	list<ClausulaCase*> clausulas;
	Sentencia* sentencia_defecto;
	void Interpretar();

public:
	SentenciaCase(Expresion* evaluacion,list<ClausulaCase*> clausulas,Sentencia* stmt_defecto);
	~SentenciaCase(void);
	void SetEvaluacion(Expresion* expr);
	void SetClausulas(list<ClausulaCase*> clausulas);
	void SetSentenciaDefecto(Sentencia* stmt);

	Expresion* GetEvaluacion();
	list<ClausulaCase*> GetClausulas();
	Sentencia* GetSentenciaDefecto();
	void validarSemantica();
};

