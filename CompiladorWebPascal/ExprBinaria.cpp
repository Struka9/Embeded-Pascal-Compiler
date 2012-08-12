#include "ExprBinaria.h"


void ExprBinaria::SetOpOne(Expresion* expr)
{
	this->op1 = expr;
}

void ExprBinaria::SetOpTwo(Expresion* expr)
{
	this->op2 = expr;
}

Expresion* ExprBinaria::GetOpOne()
{
	return op1;
}

Expresion* ExprBinaria::GetOpTwo()
{
	return op2;
}