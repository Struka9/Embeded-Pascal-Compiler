#pragma once
#include "Sentencia.h"
#include "Expresion.h"
#include "ValorBooleano.h"
class SentenciaRepeat :
	public Sentencia
{
private:
	Sentencia* codigo;
	Expresion* condicion;
	void Interpretar();
public:
	SentenciaRepeat(Sentencia* codigo,Expresion* condicion);
	~SentenciaRepeat(void);
	void SetCodigo(Sentencia* stmt);
	void SetCondicion(Expresion* expr);

	Sentencia* GetCodigo();
	Expresion* GetCondicion();
	void validarSemantica();
};

