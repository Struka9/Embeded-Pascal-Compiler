#include "ValorRegistro.h"

ValorRegistro::ValorRegistro()
{
}

ValorRegistro::ValorRegistro(map<string,Valor*>campos)
{
	this->valores_campos = campos;
}

ValorRegistro::ValorRegistro(Registro* t_reg)
{
	ListaVariables* l_vars = t_reg->GetCampos();
	list<string> nom_campos = l_vars->GetNombreCampos();
	list<string>::iterator it = nom_campos.begin();

	for ( ;it != nom_campos.end() ; it++)
	{
		string nom_campo = (*it);
		Tipo* t = l_vars->get(nom_campo);

		switch ( t->GetTipo() )
		{
		case t_entero:
			valores_campos[ nom_campo ] = new ValorEntero();
			//valores_campos.insert( pair<string,Valor*>(nom_campo,new ValorEntero()) );
			break;

		case t_real:
			valores_campos[ nom_campo ] = new ValorReal();
			//valores_campos.insert(pair<string,Valor*>(nom_campo,new ValorReal() ) );
			break;

		case t_boolean:
			//valores_campos.insert(pair<string,Valor*>(nom_campo,new ValorBooleano() ) );
			valores_campos[ nom_campo ] = new ValorBooleano();
			break;

		case t_caracter:
			//valores_campos.insert(pair<string,Valor*>(nom_campo,new ValorCaracter() ) );
			valores_campos[nom_campo]=new ValorCaracter();
			break;

		case t_cadena:
			//valores_campos.insert(pair<string,Valor*>(nom_campo,new ValorCadena() ) );
			valores_campos[nom_campo] = new ValorCadena();
			break;

		case t_registro:
			//valores_campos.insert(pair<string,Valor*>(nom_campo,new ValorRegistro( (Registro*)t) ) );
			valores_campos[nom_campo] = new ValorRegistro( (Registro*)t );
			break;

		case t_arreglo:
			//valores_campos.insert( pair<string,Valor*>(nom_campo,new ValorArreglo( (Arreglo*)t) ) );
			valores_campos[nom_campo] = new ValorArreglo( (Arreglo*)t);
			break;

		}

	}
}

ValorRegistro::~ValorRegistro(void)
{
}


tipo_valor ValorRegistro::GetTipoValor()
{
	return registro;
}

Valor* ValorRegistro::clone()
{
	map<string,Valor*> copia_valores;
	//std::copy( this->valores_campos.begin(),this->valores_campos.end(),copia_valores.begin() );
	copia_valores = this->valores_campos;
	ValorRegistro* copia = new ValorRegistro(copia_valores);


	return copia;
}

Valor* ValorRegistro::GetVal(string nom_campo)
{
	map<string,Valor*>::iterator it = valores_campos.find(nom_campo);

	if ( it == valores_campos.end() )
		return NULL;

	return it->second;
}

void ValorRegistro::SetVal(string nom_campo,Valor* val)
{
	//valores_campos.insert( pair<string,Valor*>(nom_campo,val) );
	valores_campos[nom_campo] = val;
}