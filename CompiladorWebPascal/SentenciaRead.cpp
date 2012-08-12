#include "SentenciaRead.h"


SentenciaRead::SentenciaRead(Identificador* id)
{
	SetId(id);
}


SentenciaRead::~SentenciaRead(void)
{
	delete id;
	delete siguiente;
}

void SentenciaRead::SetId(Identificador* id)
{
	this->id = id;
}

Identificador* SentenciaRead::GetId()
{
	return id;
}

void SentenciaRead::validarSemantica()
{
	Tipo* t = id->validarSemantico();

	if ( t->GetTipo() == t_registro )
		throw SemanticException("La sentencia read no es aplicable a tipo registro");

	if ( t->GetTipo() == t_arreglo )
		throw SemanticException("La sentencia read no es aplicable a tipo arreglo");
}

void SentenciaRead::Interpretar()
{
	Valor* v_guardar;
	Tipo* t_id = id->validarSemantico();

	if ( t_id->GetTipo() == t_entero )
	{
		int entero;
		cin>>entero;

		v_guardar = new ValorEntero( entero);
	}
	else if ( t_id->GetTipo() == t_real )
	{
		double n_real;
		cin>>n_real;

		v_guardar = new ValorReal(n_real);
	}
	else if ( t_id->GetTipo() == t_cadena )
	{
		string cadena;
		cin>>cadena;

		v_guardar = new ValorCadena(cadena);
	}
	else if ( t_id->GetTipo() == t_caracter )
	{
		string caracter;
		cin>>caracter;
		
		v_guardar = new ValorCaracter( caracter.substr(0,1) );
	}
	else if ( t_id->GetTipo() == t_boolean )
	{
		int entero;
		cin>>entero;

		if ( entero == 0)
			v_guardar =  new ValorBooleano(true);
		else
			v_guardar = new ValorBooleano(false);
	}

	id->GuardarEnTablaValores( v_guardar );
}