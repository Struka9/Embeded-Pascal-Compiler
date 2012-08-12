#include "Registro.h"


Registro::Registro(ListaVariables* campos)
{
	SetCampos(campos);
}


Registro::~Registro(void)
{
	delete campos;
}

void Registro::SetCampos(ListaVariables* campos)
{
	this->campos = campos;
}

ListaVariables* Registro::GetCampos()
{
	return campos;
}

tipo_dato Registro::GetTipo()
{
	return t_registro;
}

bool Registro::EsEquivalente(Tipo* t)
{
	if ( t->GetTipo() != t_registro )
		return false;

	Registro* tipo_registro = (Registro*)t;
	list<string> mis_campos = this->campos->GetNombreCampos();
	list<string> tus_campos = tipo_registro->GetCampos()->GetNombreCampos();
	if ( tus_campos.size() != mis_campos.size() )
		return false;

	list<string>::iterator it_mio = mis_campos.begin();
	list<string>::iterator it_tuyo = tus_campos.begin();

	for ( ;it_mio != mis_campos.end() ; it_mio++,it_tuyo++ )
	{
		string mi_id = (*it_mio);
		string tu_id = (*it_tuyo);

		if ( !(this->campos->get( mi_id )->EsEquivalente( tipo_registro->GetCampos()->get(tu_id) ) ) )
			return false;
	}

	return true;

}