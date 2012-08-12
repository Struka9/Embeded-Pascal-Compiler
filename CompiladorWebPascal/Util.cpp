#include "Util.h"

bool Util::EsDigito(char c)
{
	return ( c >=48 && c<=57 );
}

bool Util::EsLetra(char c)
{
	return ( (c>=65 && c<=90)|| (c>=97 && c<=122) );
}

bool Util::EsHexDig( char c)
{
	return ( c>=48 && c<=57 || c>=65 && c<=70 || c>=97 && c<=102 );
}

bool Util::EsOctalDig(char c)
{
	return ( c>=48 && c<=55 );
}

char Util::ToUpper(char c)
{
	return (char)toupper(c);
}

