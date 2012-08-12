#include "ClausulaCase.h"


ClausulaCase::ClausulaCase(ConstanteLiteral* constante, Sentencia* codigo)
{
	SetConstante(constante);
	SetCodigo(codigo);
}


ClausulaCase::~ClausulaCase(void)
{
	delete codigo;
	delete constante;
}


void ClausulaCase::SetCodigo(Sentencia* stmt)
{
	this->codigo = stmt;
}

Sentencia* ClausulaCase::GetCodigo()
{
	return codigo;
}

void ClausulaCase::SetConstante(ConstanteLiteral* constante)
{
	this->constante = constante;
}

ConstanteLiteral* ClausulaCase::GetConstante()
{
	return this->constante;
}