#include "DeclaracionFuncion.h"


DeclaracionFuncion::DeclaracionFuncion(string nombre_funcion,list<Parametro*> lista_parametros,
	Sentencia* cuerpo_func,Tipo* tipo)
{
	SetTipo(tipo);
	SetNombreFuncion(nombre_funcion);
	SetParametros(lista_parametros);
	SetCuerpoFunc(cuerpo_func);
}


DeclaracionFuncion::~DeclaracionFuncion(void)
{
	delete cuerpo_funcion;
}

void DeclaracionFuncion::SetCuerpoFunc(Sentencia* stmt)
{
	this->cuerpo_funcion = stmt;
}

void DeclaracionFuncion::SetNombreFuncion(string str)
{
	this->nom_func = str;
}

void DeclaracionFuncion::SetParametros( list<Parametro*> params )
{
	this->lista_parametros = params;
}

Sentencia* DeclaracionFuncion::GetCuerpoFuncion()
{
	return this->cuerpo_funcion;
}

string DeclaracionFuncion::GetNombre()
{
	return nom_func;
}

list<Parametro*> DeclaracionFuncion::GetParametros()
{
	return lista_parametros;
}

void DeclaracionFuncion::SetTipo(Tipo* t)
{
	this->tipo = t;
}

Tipo* DeclaracionFuncion::GetTipo()
{
	return tipo;
}

void DeclaracionFuncion::ValidarSemantica()
{
	//Verificar que ninguna variable global o tipo tenga el nombre de la funcion
	Tipo* t_error = InformacionSemantica::GetInstance()->GetFromTablaSimbolos(nom_func);
	if ( t_error != NULL )
		throw SemanticException("No se puede declarar una funcion con el nombre de una variable global");

	t_error = InformacionSemantica::GetInstance()->GetFromTablaTipos(nom_func);

	if ( t_error != NULL )
		throw SemanticException("No se puede declarar una funcion con el nombre de un tipo");

	//TODO:Verificar el nombre de los parametros
	list<Parametro*>::iterator outer_it = lista_parametros.begin();
	

	InformacionSemantica::GetInstance()->SetContexto( nom_func );
	/*
	map<string,Parametro*> lista_nombres;
	for ( ; outer_it != lista_parametros.end() ; ++outer_it )
	{
		/*
		for (list<Parametro*>::iterator inner_it = (outer_it++) ; inner_it != lista_parametros.end() ; ++inner_it)
		{
			Parametro* i = (*outer_it);
			Parametro* j = (*inner_it);

			if ( i->EsIgual(  j ) )
				throw SemanticException("Dos parametros no pueden ser iguales dentro de una misma funcion");
		}
		
		//lista_nombres.insert( pair<string,Parametro*>( (*outer_it)->GetNombre(), (*outer_it) );
		InformacionSemantica::GetInstance()->InsertarVarEnContexto(nom_func,(*outer_it)->GetNombre(),(*outer_it)->GetTipo() );

		
	}	
	*/
	
	//Meter los parametros a la tabla de simbolos de la funcion

	cuerpo_funcion->validacionSemantica();

}

