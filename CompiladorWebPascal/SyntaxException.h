#pragma once
#include <stdexcept>
#include <string>
using namespace std;

class SyntaxException: public runtime_error
{
	
private:
	int linea;
	string mensaje;
public:
	string GetMensaje();
	SyntaxException(string mensaje,int linea);
	~SyntaxException(void);
};

