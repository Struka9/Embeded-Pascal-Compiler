#pragma once
#include "Sentencia.h"
#include "Expresion.h"
#include "ValorBooleano.h"
class SentenciaWhile :
	public Sentencia
{
private:
	Expresion* condicion;
	Sentencia* codigo;
	void Interpretar();

public:
	SentenciaWhile( Expresion* condicion , Sentencia* codigo);
	~SentenciaWhile(void);

	void SetCondicion(Expresion* expr );
	Expresion* GetCondicion();

	void SetCodigo(Sentencia* stmt );
	Sentencia* GetCodigo();
	void validarSemantica();
};

