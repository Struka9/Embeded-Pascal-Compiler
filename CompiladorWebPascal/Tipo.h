#pragma once
enum tipo_dato{t_entero,t_real,t_boolean,t_caracter,t_cadena,t_arreglo,t_registro};
class Tipo
{
private:
	//TODO: WTF?
	int i;
public:
	virtual tipo_dato GetTipo()=0;
	virtual bool EsEquivalente(Tipo* t)=0;
};

