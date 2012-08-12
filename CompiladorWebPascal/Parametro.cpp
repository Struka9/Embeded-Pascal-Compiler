#include "Parametro.h"

Parametro::Parametro(string nom_parametro,bool esReferencia,Tipo* tipo)
{
	SetNombre(nom_parametro);
	SetReferencia(esReferencia);
	SetTipo(tipo);
}

Parametro::~Parametro()
{
	delete tipo;
}

void Parametro::SetNombre(string str)
{
	this->nom_parametro = str;
}

void Parametro::SetReferencia(bool esReferencia)
{
	this->esPorReferencia = esReferencia;
}

void Parametro::SetTipo(Tipo* tipo)
{
	this->tipo = tipo;
}

string Parametro::GetNombre()
{
	return this->nom_parametro;
}

bool Parametro::EsPorReferencia()
{
	return this->esPorReferencia;
}

Tipo* Parametro::GetTipo()
{
	return tipo;
}

bool Parametro::EsIgual(Parametro* p)
{
	/*
	return (this->esPorReferencia == p->EsPorReferencia() &&
		this->nom_parametro.compare( p->GetNombre() ) && this->tipo->EsEquivalente( p->GetTipo() ) );
	*/
	return this->nom_parametro.compare( p->GetNombre() )==0;
}