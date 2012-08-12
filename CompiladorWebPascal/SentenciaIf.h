#pragma once
#include "Sentencia.h"
#include "Expresion.h"
#include "ValorBooleano.h"
class SentenciaIf :
	public Sentencia
{
private:
	void Interpretar();
	Expresion* condicion;
	Sentencia* verdaderoStmt;
	Sentencia* falsoStmt;
public:
	SentenciaIf(Expresion* condicion , Sentencia* verdaderoStmt, Sentencia* falsoStmt);
	~SentenciaIf(void);

	void SetCondicion(Expresion* expr);
	void SetSentenciaVerdadero(Sentencia* stmt);
	void SetSentenciaFalso(Sentencia* stmt);

	Expresion* GetCondicion();
	Sentencia* GetSentenciaVerdadero();
	Sentencia* GetSentenciaFalso();
	void validarSemantica();
};

