#pragma once
#include "Arreglo.h"
#include "Valores.h"
class ValorArreglo :
	public Valor
{
private:
	Valor* *arreglo_valores;
	int _totalpos;

public:
	void SetTipoArr(Arreglo* t_arr);
	void SetArr(Valor** arreglo,int totalpos);

	Valor* clone();
	//ValorArreglo( Valor** arreglo,int totalpos,Arreglo* t_arr);
	Arreglo* t_arr;
	ValorArreglo();
	ValorArreglo(Arreglo* t_arr);
	tipo_valor GetTipoValor();
	Valor* GetVal(int pos);
	void SetVal(int pos,Valor* val);
	~ValorArreglo(void);
};

