#include "Lexico.h"
#include "Sintactico.h"
#include "Util.h"
#include <iostream>
#include <conio.h>
#include <iomanip>
using namespace std;

int main()
{
	/*
	Lexico *archivo = new Lexico("C:\\Users\\OscarR\\Documents\\BubbleSort_pascal.txt");
	cout<< "Lexema" <<setw(20)	<<"Tipo"<<endl;
	while(true)
	{
		try{
		
		Token token = archivo->ObtenerSiguienteToken();


		cout<<std::right<<token.GetLexema()<<setw(20)<<std::right<<token.GetTipo()<<endl;
		if ( token.GetTipo() == error )
			break;

		if ( token.GetTipo() == eof )
			break;
		}
		catch ( LexicalException ex )
		{
			cout<<ex.what() << " "<< " en la linea "<<ex.GetLinea()<<endl;
		}
	}*/
	
	Sintactico* analizador_sintactico =  new Sintactico("C:\\Users\\OscarR\\Documents\\Visual Studio 2010\\Projects\\CompiladorWebPascal\\ProgramasPrueba\\Prueba1.txt");
	try
	{
		Sentencia* stmt = analizador_sintactico->GenerarArbol();
		stmt->validacionSemantica();
		stmt->Interpretacion();
	}
	catch ( LexicalException l_ex )
	{
		cout<<l_ex.what();
		_getch();
		return 0;
	}
	catch ( SyntaxException ex )
	{
		cout<<ex.GetMensaje();
		_getch();
		return 0;
	}
	catch (SemanticException se_ex)
	{
		cout<<se_ex.GetMensaje();
		_getch();
		return 0;
	}
	
	cout<<"compiliacion con exito";
	_getch();
	return 0;
}