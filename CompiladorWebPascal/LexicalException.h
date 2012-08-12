#pragma once
#include <stdexcept>
#include <string>
using namespace std;
class LexicalException :
	public runtime_error
{
private:
	string mensaje;
	int linea;

public:
	LexicalException(int linea,string mensaje);
	int GetLinea();
	~LexicalException(void);
};

