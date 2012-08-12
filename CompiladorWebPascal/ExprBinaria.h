#pragma once
#include "Expresion.h"
class ExprBinaria:public Expresion
{
protected:
	Expresion *op1, *op2;

public:
	virtual Tipo* validarSemantico()=0;
	Expresion* GetOpOne();
	Expresion* GetOpTwo();
	void SetOpOne(Expresion* expr);
	void SetOpTwo(Expresion* expr);
};

