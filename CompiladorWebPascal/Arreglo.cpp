#include "Arreglo.h"


Arreglo::Arreglo(list<LimitesRango*> limites,Tipo* of)
{
	SetLimites(limites);
	SetOf(of);
}


Arreglo::~Arreglo(void)
{
	delete of;
}

void Arreglo::SetOf(Tipo* t)
{
	this->of = t;
}

Tipo* Arreglo::GetOf()
{
	return this->of;
}

void Arreglo::SetLimites(list<LimitesRango*>lim)
{
	this->lim = lim;
}

list<LimitesRango*> Arreglo::GetLim()
{
	return lim;
}

bool Arreglo::EsEquivalente(Tipo* t)
{
	//t no es de tipo arreglo
	if ( t->GetTipo() != t_arreglo )
		return false;

	Arreglo* tipo_arreglo = (Arreglo*)t;

	//t no tiene la misma cantidad de dimensiones
	if ( tipo_arreglo->GetLim().size() != this->GetLim().size() )
		return false;

	//Para cada dimension los limites deben ser iguales
	list<LimitesRango*> tus_limites = tipo_arreglo->GetLim();
	list<LimitesRango*>::iterator it_this;
	list<LimitesRango*>::iterator it_t = tus_limites.begin();
	for (it_this = lim.begin() ; it_this != lim.end() ; ++it_this,++it_t )
	{
		LimitesRango* mi_lim = (*it_this);
		LimitesRango* tu_lim = (*it_t);
		if ( mi_lim->GetInferior() != tu_lim->GetInferior() ||
			mi_lim->GetSuperior() != tu_lim->GetSuperior() )
			return false;
	}
	
	return of->EsEquivalente( tipo_arreglo->GetOf() );
}

tipo_dato Arreglo::GetTipo()
{
	return t_arreglo;
}

int Arreglo::GetSizeOfIndex(int indice)
{
	int size = 1;

	list<LimitesRango*>::iterator it = lim.begin();
	std::advance(it,indice+1);

	for ( ;it != lim.end() ; it++)
	{
		size*= (*it)->GetCant();
	}

	return size;
}

int Arreglo::mapeo(int n_lim,int index)
{
	list<LimitesRango*>::iterator it= lim.begin();
	std::advance(it,n_lim);

	return index-(*it)->GetInferior();
}