#pragma once
enum tipo_valor{entero,cadena,caracter,boolean,real,registro,arreglo};
class Valor
{
public:
	virtual tipo_valor GetTipoValor() = 0;
	virtual Valor* clone()=0;
};

