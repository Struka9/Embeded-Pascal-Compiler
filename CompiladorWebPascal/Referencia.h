#pragma once
#include "Qualifier.h"
#include <string>
using namespace std;

class Referencia :
	public Qualifier
{
private:
	string nom_campo;
public:
	Referencia(string nom_campo);
	~Referencia(void);
	void SetCampo(string str);
	string GetCampo();
	tipo_qualifier GetTipo();
};

