#include "Token.h"

Token::Token()
{
}

Token::~Token()
{
}

string Token::GetLexema()
{
	return lexema;
}

tipo_token Token::GetTipo()
{
	return tipo;
}

void Token::SetLexema(string lexema)
{
	this->lexema = lexema;
}

void Token::SetTipo(tipo_token tipo)
{
	this->tipo = tipo;
}

void Token::SetLineaAparicion(int linea)
{
	this->linea = linea;
}

int Token::GetLineaAparicion()
{
	return linea;
}