#pragma once
#include "Tipo.h"
#include "ListaVariables.h"
class Registro :
	public Tipo
{
private:
	ListaVariables* campos;
public:
	Registro(ListaVariables* campos);
	~Registro(void);

	ListaVariables* GetCampos();
	void SetCampos(ListaVariables* campos);

	tipo_dato GetTipo();
	bool EsEquivalente(Tipo* t);
};

