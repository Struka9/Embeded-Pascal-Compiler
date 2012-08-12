#pragma once
#include "Sentencia.h"
#include "ConstanteLiteral.h"

class ClausulaCase
{
private:
	ConstanteLiteral* constante;
	Sentencia* codigo;
public:
	ClausulaCase(ConstanteLiteral* constante, Sentencia* codigo);
	void SetCodigo(Sentencia* stmt);
	void SetConstante(ConstanteLiteral* cnst);

	Sentencia* GetCodigo();
	ConstanteLiteral* GetConstante();
	~ClausulaCase(void);
};

