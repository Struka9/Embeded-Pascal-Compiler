#include "ValorArreglo.h"

ValorArreglo::ValorArreglo()
{
	this->_totalpos = 0;
}

ValorArreglo::ValorArreglo(Arreglo* t_arr)
{
	this->t_arr = t_arr;
	list<LimitesRango*>lista_rangos = t_arr->GetLim();
	list<LimitesRango*>::iterator it = lista_rangos.begin();

	int num_elementos = (*it)->GetCant();
	it++;
	for ( ; it != lista_rangos.end() ; it++)
	{
		num_elementos *= (*it)->GetCant();
	}

	arreglo_valores = new Valor*[num_elementos];

	Valor* inicializacion;
	Tipo* arreglo_of = t_arr->GetOf();
	switch( arreglo_of->GetTipo() ) 
	{
		case t_entero:
			inicializacion = new ValorEntero();
			break;

		case t_real:
			inicializacion = new ValorReal();
			break;

		case t_boolean:
			inicializacion = new ValorBooleano();
			break;

		case t_caracter:
			inicializacion = new ValorCaracter();
			break;

		case t_cadena:
			inicializacion = new ValorCadena();
			break;

		case t_registro:
			inicializacion = new ValorRegistro((Registro*)arreglo_of);
			break;

		case t_arreglo:
			inicializacion = new ValorArreglo((Arreglo*)arreglo_of);
			break;
	}

	for ( int i = 0 ; i < num_elementos ; i++)
		arreglo_valores[i] = inicializacion;

	_totalpos = num_elementos;

}


ValorArreglo::~ValorArreglo(void)
{
}

void ValorArreglo::SetArr( Valor** arreglo_valores,int totalpos )
{
	this->_totalpos = totalpos;
	//this->arreglo_valores = arreglo_valores;
	for ( int i =0 ; i <totalpos; i++)
		this->arreglo_valores[i] = arreglo_valores[i]->clone();
}

void ValorArreglo::SetTipoArr(Arreglo* t_arr)
{
	this->t_arr = t_arr;
}

Valor* ValorArreglo::clone()
{
	//Valor* *_nuevo = new Valor*[_totalpos];
	//memcpy(_nuevo,arreglo_valores,_totalpos);
	

	ValorArreglo* copia = new ValorArreglo(this->t_arr);
	copia->SetArr(this->arreglo_valores ,_totalpos);
	//copia->SetTipoArr( this->t_arr );
	return copia;
}

Valor* ValorArreglo::GetVal(int pos )
{
	return arreglo_valores[pos];
}

void ValorArreglo::SetVal(int pos,Valor* val)
{
	arreglo_valores[pos] = val;
}

tipo_valor ValorArreglo::GetTipoValor()
{
	return arreglo;
}

