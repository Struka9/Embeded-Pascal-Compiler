#pragma once

class Sentencia
{
protected:
	Sentencia* siguiente;
	virtual void validarSemantica()=0;
	virtual void Interpretar()=0;
public:
	Sentencia* GetSiguiente();
	void SetSiguiente(Sentencia* siguiente);
	
	void Interpretacion()
	{
		Interpretar();
		if ( siguiente != 0 )
			siguiente->Interpretacion();
	}

	void validacionSemantica()
	{
		validarSemantica();
		if ( siguiente != 0)
			siguiente->validacionSemantica();
	}
};

