#pragma once
#include "Expresion.h"

class ExpresionUnaria :
	public Expresion
{
protected:
	Expresion* expr;

public:
	virtual Tipo* validarSemantico()= 0;
	Expresion* GetExpr();
	void SetExpr(Expresion* expr);
};

