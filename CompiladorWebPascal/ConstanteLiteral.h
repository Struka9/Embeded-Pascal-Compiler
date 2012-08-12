#pragma once

#include "Expresion.h"
class ConstanteLiteral:public Expresion
{
public:
	virtual Tipo* validarSemantico()=0;
};

