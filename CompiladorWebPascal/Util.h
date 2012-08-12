#pragma once
#include <cctype>

class Util
{
public:
	static bool EsDigito(char c);
	static bool EsHexDig(char c);
	static bool EsOctalDig(char c);
	static bool EsLetra(char c);
	static char ToUpper(char c);
};

