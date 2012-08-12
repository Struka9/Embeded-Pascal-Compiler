#pragma once
#include "Tipo.h"
#include "Valor.h"
#include "SemanticException.h"
#include "InformacionSemantica.h"
class Expresion
{
public:
	virtual Tipo* validarSemantico()=0;
	virtual Valor* interpretar() = 0;
};

