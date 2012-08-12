#pragma once
#include "sentencia.h"
class ListaSentencias :
	public Sentencia
{
private:
	Sentencia* lista_stmt;
	void validarSemantica();
	void Interpretar();
public:
	ListaSentencias(Sentencia* lista_stmt);
	~ListaSentencias(void);

	void SetListaSentencias(Sentencia* stmt);
	Sentencia* GetListaSentencias();
};

