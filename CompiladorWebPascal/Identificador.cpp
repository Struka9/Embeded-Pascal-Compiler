#include "Identificador.h"


Identificador::Identificador(string nombre,list<Qualifier*>qualifiers)
{
	SetId(nombre);
	SetQualifiers(qualifiers);
}


void Identificador::SetId(string nombre)
{
	this->id = nombre;
}

string Identificador::GetId()
{
	return id;
}

void Identificador::SetQualifiers(list<Qualifier*> qualifiers)
{
	this->qualifiers = qualifiers;
}

list<Qualifier*> Identificador::GetQualifiers()
{
	return qualifiers;
}

Tipo* Identificador::validarSemantico()
{
	//t_actual contendra el tipo del id o qualifier que se esta evaluando
	Tipo* t_actual = InformacionSemantica::GetInstance()->GetFromTablaSimbolos(id);

	if ( t_actual == 0 )
		throw  SemanticException( "Variable " + id + " no existe!");

	list<Qualifier*>::iterator qualifier_iterator = qualifiers.begin();

	for ( ; qualifier_iterator != qualifiers.end() ; qualifier_iterator++ )
	{
		Qualifier* qual = (*qualifier_iterator);

		if ( qual->GetTipo() == qt_index )
		{
			if ( t_actual->GetTipo() != t_arreglo )
				throw  SemanticException("No es un arrelgo Identificador.cpp/48");

			Indexacion* index = (Indexacion*)qual;
			Arreglo* arr = (Arreglo*)t_actual;

			if ( arr->GetLim().size() != index->GetIndices().size() )
				throw  SemanticException("El numero de limites no coincide Identificador.cpp/54");

			Entero* tipo_entero =(Entero*) InformacionSemantica::GetInstance()->GetTablaTipos().find("INTEGER")->second;
			list<Expresion*>lista_indices =  index->GetIndices();
			list<Expresion*>::iterator iterator_expresiones = lista_indices.begin();
			
			for ( ; iterator_expresiones != lista_indices.end() ; iterator_expresiones++ )
			{
				if ( ! ( (*iterator_expresiones)->validarSemantico()->EsEquivalente( tipo_entero ) ) )
					throw SemanticException("Solo se permite indexacion con expresiones tipo entero");
			}

			t_actual = arr->GetOf();
		}
		else if ( qual->GetTipo() == qt_campo )
		{
			if ( t_actual->GetTipo() != t_registro )
				throw SemanticException("El tipo no es un registro Identificador.cpp");

			Referencia* qual_referencia = (Referencia*)qual;
			Registro* tipo_registro = (Registro*)t_actual; 
			string campo = qual_referencia->GetCampo();
			Tipo* tipo_campo = tipo_registro->GetCampos()->get( campo );

			if ( tipo_campo == 0 )
				throw SemanticException("El campo " + campo + " no esta definido Identificador.cpp");

			t_actual = tipo_campo;
		}


	}

	return t_actual;
	
}

Valor* Identificador::interpretar()
{
	Valor* val_ret = InformacionInterpretacion::GetInstance()->GetFromTablaValores( id );
	list<Qualifier*>::iterator it = qualifiers.begin();


	for ( ; it != qualifiers.end() ; it++ )
	{
		if( (*it)->GetTipo()== qt_index )
		{
			ValorArreglo* v_arr = (ValorArreglo*)val_ret;
			//TODO: Indexacion
			Indexacion* indice = (Indexacion*)(*it);
			list<Expresion*> lista_expr = indice->GetIndices();
			list<Expresion*>::iterator it_dim = lista_expr.begin();
			int index = 0;
			for ( int i = 0; it_dim != lista_expr.end() ; it_dim++,i++ )
			{
				
				/*
				ValorEntero* v_expr = (ValorEntero*)(*it_dim)->interpretar();
				index += v_expr->GetVal() * v_arr->t_arr->GetSizeOfIndex(i);
				*/

				

				ValorEntero* v_expr = (ValorEntero*)(*it_dim)->interpretar();
				int mapeo = v_arr->t_arr->mapeo(i,v_expr->GetVal() );
				//index += v_expr->GetVal() * v_arr->t_arr->GetSizeOfIndex(i);
				index += mapeo * v_arr->t_arr->GetSizeOfIndex(i);
				
			}

			val_ret = v_arr->GetVal(index);

		}
		else
		{
			Referencia* ref = (Referencia*)(*it);
			string nom_campo = ref->GetCampo();

			ValorRegistro* v_reg = (ValorRegistro*)val_ret;
			val_ret = v_reg->GetVal(nom_campo);
		}
	}
	

	return val_ret->clone();
}


void Identificador::GuardarEnTablaValores(Valor* val)
{

	Valor* val_actual = InformacionInterpretacion::GetInstance()->GetFromTablaValores( id );
	list<Qualifier*>::iterator it = qualifiers.begin();
	list<Valor*> valores;

	for ( ; it != qualifiers.end() ; it++ )
	{
		valores.push_back(val_actual);
		if( (*it)->GetTipo()== qt_index )
		{
			ValorArreglo* v_arr = (ValorArreglo*)val_actual;
			Indexacion* indice = (Indexacion*)(*it);
		
			list<Expresion*> lista_expr = indice->GetIndices();
			list<Expresion*>::iterator it_dim = lista_expr.begin();
			int index = 0;
			for ( int i = 0; it_dim != lista_expr.end() ; it_dim++,i++ )
			{
				ValorEntero* v_expr = (ValorEntero*)(*it_dim)->interpretar();
				int mapeo = v_arr->t_arr->mapeo(i,v_expr->GetVal() );
				//index += v_expr->GetVal() * v_arr->t_arr->GetSizeOfIndex(i);
				index += mapeo * v_arr->t_arr->GetSizeOfIndex(i);

			}

			val_actual = v_arr->GetVal(index)->clone();
		}
		else
		{
			Referencia* ref = (Referencia*)(*it);
			string nom_campo = ref->GetCampo();

			ValorRegistro* v_reg = (ValorRegistro*)val_actual;
			val_actual = v_reg->GetVal(nom_campo)->clone();
		}
	}

	val_actual = val->clone();

	list<Qualifier*>::reverse_iterator r_it_qualifier = qualifiers.rbegin() ;
	//r_it_qualifier++;
	list<Valor*>::reverse_iterator r_it_valor = valores.rbegin();
	//r_it_valor++;

	for ( ; r_it_valor != valores.rend() ; r_it_valor++, r_it_qualifier++ )
	{
		if ( (*r_it_valor)->GetTipoValor() == registro )
		//if ( ((Referencia*)(*r_it_qualifier) )->GetTipo() == qt_campo  )
		{
			Referencia* ref = (Referencia*)(*r_it_qualifier);
			string nom_campo =ref->GetCampo();

			Valor* nuevo_clon = val_actual->clone();
			(( ValorRegistro*)(*r_it_valor))->SetVal(nom_campo,nuevo_clon);
		}
		else
			if ( (*r_it_valor)->GetTipoValor() == arreglo )
			//if ( ((Indexacion*)(*r_it_qualifier))->GetTipo() == qt_index)
			{
				Indexacion* indice = (Indexacion*)(*r_it_qualifier);

				list<Expresion*> lista_expr = indice->GetIndices();
				list<Expresion*>::iterator it_dim = lista_expr.begin();
				int index = 0;
				for ( int i = 0; it_dim != lista_expr.end() ; it_dim++,i++ )
				{
					



					ValorEntero* v_expr = (ValorEntero*)(*it_dim)->interpretar();


					int mapeo = ((ValorArreglo*)(*r_it_valor))->t_arr->mapeo(i,v_expr->GetVal() );
				   //index += v_expr->GetVal() * v_arr->t_arr->GetSizeOfIndex(i);
					index += mapeo * ((ValorArreglo*)(*r_it_valor))->t_arr->GetSizeOfIndex(i);

					
					//index += v_expr->GetVal() * ((ValorArreglo*)(*r_it_valor))->t_arr->GetSizeOfIndex(i);
					


				}

				Valor* nuevo_clon = val_actual->clone();
				((ValorArreglo*)(*r_it_valor))->SetVal(index,nuevo_clon);
			}

			val_actual = (*r_it_valor)->clone();
	}

	Valor* nuevo =val_actual->clone();
	InformacionInterpretacion::GetInstance()->InsertarEnTablaValores( id,nuevo);
	
}