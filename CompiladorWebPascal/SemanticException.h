#pragma once
#include <stdexcept>
#include <string>
using namespace std;
class SemanticException :
	public runtime_error
{
private:
	string msj;
public:
	SemanticException(string mensaje);
	~SemanticException(void);

	string GetMensaje();
};

