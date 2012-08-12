#include "Lexico.h"

Lexico::Lexico(string nombre_archivo)
{
	this->codigo_fuente = new LectorArchivo(nombre_archivo);
	this->codigo_fuente->ObtenerContenido();
	MapInit();
	linea_actual = 1;
	modo_html = false;
}

Lexico::~Lexico(void)
{
}

void Lexico::MapInit()
{
	Token token;
	
	//Keywords
	token.SetLexema("IF");
	token.SetTipo(kw_if);
	palabras_reservadas.insert(pair<string,Token>("IF",token) );

	token.SetLexema("AND");
	token.SetTipo(op_and);
	palabras_reservadas.insert(pair<string,Token>("AND",token) );

	token.SetLexema("ARRAY");
	token.SetTipo(kw_array);
	palabras_reservadas.insert( pair<string,Token>("ARRAY",token) );

	token.SetLexema("BEGIN");
	token.SetTipo(kw_begin);
	palabras_reservadas.insert( pair<string,Token>("BEGIN",token) );

	token.SetLexema("CASE");
	token.SetTipo(kw_case);
	palabras_reservadas.insert( pair<string,Token>("CASE",token) );

	token.SetLexema("DIV");
	token.SetTipo(op_divent);
	palabras_reservadas.insert( pair<string,Token>("DIV",token) );
	
	token.SetLexema("DO");
	token.SetTipo(kw_do);
	palabras_reservadas.insert( pair<string,Token>("DO",token) );

	token.SetLexema("DOWNTO");
	token.SetTipo(kw_downto);
	palabras_reservadas.insert( pair<string,Token>("DOWNTO",token) );

	token.SetLexema("ELSE");
	token.SetTipo(kw_else);
	palabras_reservadas.insert( pair<string,Token>("ELSE",token) );

	token.SetLexema("END");
	token.SetTipo(kw_end);
	palabras_reservadas.insert( pair<string,Token>("END",token) );

	token.SetLexema("FOR");
	token.SetTipo(kw_for);
	palabras_reservadas.insert( pair<string,Token>("FOR",token) );

	token.SetLexema("FUNCTION");
	token.SetTipo(kw_funcion);
	palabras_reservadas.insert( pair<string,Token>("FUNCTION",token) );

	token.SetLexema("MOD");
	token.SetTipo(op_mod);
	palabras_reservadas.insert( pair<string,Token>("MOD",token) );

	token.SetLexema("NOT");
	token.SetTipo(kw_not);
	palabras_reservadas.insert( pair<string,Token>("NOT",token) );

	token.SetLexema("OF");
	token.SetTipo(kw_of);
	palabras_reservadas.insert( pair<string,Token>("OF",token) );

	token.SetLexema("OR");
	token.SetTipo(kw_or);
	palabras_reservadas.insert( pair<string,Token>("OR",token) );

	token.SetLexema("PROCEDURE");
	token.SetTipo(kw_procedimiento);
	palabras_reservadas.insert( pair<string,Token>("PROCEDURE",token) );

	token.SetLexema("PROGRAM");
	token.SetTipo(kw_program);
	palabras_reservadas.insert( pair<string,Token>("PROGRAM",token) );

	token.SetLexema("RECORD");
	token.SetTipo(kw_record);
	palabras_reservadas.insert( pair<string,Token>("RECORD",token) );

	token.SetLexema("REPEAT");
	token.SetTipo(kw_repeat);
	palabras_reservadas.insert( pair<string,Token>("REPEAT",token) );

	token.SetLexema("THEN");
	token.SetTipo(kw_then);
	palabras_reservadas.insert( pair<string,Token>("THEN",token) );

	token.SetLexema("TO");
	token.SetTipo( kw_to);
	palabras_reservadas.insert( pair<string,Token>("TO",token) );

	token.SetLexema("TYPE");
	token.SetTipo(kw_tipo);
	palabras_reservadas.insert( pair<string,Token>("TYPE",token) );

	token.SetLexema("UNTIL");
	token.SetTipo(kw_until);
	palabras_reservadas.insert( pair<string,Token>("UNTIL",token) );

	token.SetLexema("VAR");
	token.SetTipo(kw_var);
	palabras_reservadas.insert( pair<string,Token>("VAR",token) );

	token.SetLexema("WHILE");
	token.SetTipo(kw_while);
	palabras_reservadas.insert( pair<string,Token>("WHILE",token) );

	token.SetLexema("WRITELN");
	token.SetTipo(kw_write);
	palabras_reservadas.insert( pair<string,Token>("WRITELN",token) );

	token.SetLexema("READ");
	token.SetTipo(kw_read);
	palabras_reservadas.insert(pair<string,Token>("READ",token) );

	//Tipos Primitivos
	token.SetLexema("INTEGER");
	token.SetTipo(kw_entero);
	palabras_reservadas.insert( pair<string,Token>("INTEGER",token) );

	token.SetLexema("REAL");
	token.SetTipo(kw_real);
	palabras_reservadas.insert( pair<string,Token>("REAL",token) );

	token.SetLexema("STRING");
	token.SetTipo( kw_string );
	palabras_reservadas.insert( pair<string,Token>("STRING",token) );

	token.SetLexema("BOOLEAN");
	token.SetTipo(kw_bool);
	palabras_reservadas.insert( pair<string,Token>("BOOLEAN",token) );

	token.SetLexema("CHAR");
	token.SetTipo(kw_char);
	palabras_reservadas.insert( pair<string,Token>("CHAR",token) );

	//Constantes booleanas
	token.SetLexema("TRUE");
	token.SetTipo(lit_boolean);
	palabras_reservadas.insert(pair<string,Token>("TRUE",token));

	token.SetLexema("FALSE");
	palabras_reservadas.insert(pair<string,Token>("FALSE",token));

}

Token Lexico::ObtenerSiguienteToken()
{
	if ( modo_html )
		return ObtenerSiguienteTokenHTML();
	else
		return ObtenerSiguienteTokenPascal();
}

Token Lexico::ObtenerSiguienteTokenPascal()
{
	Token token;
	string lexema;
	char c;
	int estado_automata = 0; //Estado inicial del automata
	int longitud_cadenas = 0;

	while (true)
	{
		c = codigo_fuente->LeerCaracter();
		switch ( estado_automata )
		{
			//Estado 0 se encarga de "comerse" los espacios en blanco y caracter de nueva linea
		case 0:
			if ( Util::EsLetra( c ) )
			{
				lexema+= Util::ToUpper(c);
				estado_automata = 1;
				codigo_fuente->Avanzar();
			}
			else if (  c == '+'  )//Operadores aditivos
			{
				lexema+=c;
				estado_automata = 2;
				codigo_fuente->Avanzar();
			}
			else if ( c == '-' )
			{
				lexema+=c;
				codigo_fuente->Avanzar();
				token.SetLexema(lexema);
				token.SetTipo(op_resta);
				return token;
			}
			else if( c == '*' )
			{
				lexema+=c;
				codigo_fuente->Avanzar();
				token.SetLexema(lexema);
				token.SetTipo( op_mul );
				return token;
			}
			else if ( c == '=' )
			{
				lexema+=c;
				codigo_fuente->Avanzar();
				token.SetLexema(lexema);
				token.SetTipo( op_igual );
				return token;
			}
			else if( c== '\n')//Se "come" los caracteres de nueva linea
			{
				linea_actual++;
				estado_automata = 0;
				codigo_fuente->Avanzar();
			}
			else if( c== EOF ) //El archivo llego a su fin
			{
				estado_automata = 4;
			}
			else if ( c== ' ' || c=='\t' )//Espacios y tabulaciones
			{
				estado_automata = 0;
				codigo_fuente->Avanzar();
			}
			else if( c=='/' )//Comentarios u operador de division
			{
				estado_automata = 5;
				codigo_fuente->Avanzar();
			}
			else if( Util::EsDigito( c ) && c != '0' ) //Decimal
			{
				lexema+=c;
				estado_automata = 7;
				codigo_fuente->Avanzar();
			}
			else if( c == '0')//Octal
			{
				lexema+=c;
				estado_automata = 8;
				codigo_fuente->Avanzar();
			}
			else if ( c == '$' )//Hexadecimal
			{
				lexema+=c;
				estado_automata=12;
				codigo_fuente->Avanzar();
			}
			else if ( c == '.' )//Punto flotante
			{
				lexema+=c;
				estado_automata = 24;
				codigo_fuente->Avanzar();
			}
			else if ( c == '\'' )//string
			{
				lexema+=c;
				estado_automata = 17;
				codigo_fuente->Avanzar();
			}
			else if ( c=='>')//operadores
			{
				lexema+=c;
				estado_automata =20;
				codigo_fuente->Avanzar();
			}
			else if (  c == '[' || c== '}' || c== ';' || c==',' || c== '{' || c== '(' || c== ')' || c ==']' )//puntacion
			{
				lexema+=c;
				estado_automata = 22;
				codigo_fuente->Avanzar();
			}
			else if ( c== ':' )
			{
				lexema+=c;
				estado_automata = 23;
				codigo_fuente->Avanzar();
			}
			else if ( c == '%' )
			{
				lexema+=c;
				estado_automata = 29;
				codigo_fuente->Avanzar();
			}
			else if ( c == '<' )
			{
				lexema+=c;
				estado_automata = 31;
				codigo_fuente->Avanzar();
			}
			else
			{
				codigo_fuente->Avanzar();
				throw LexicalException( linea_actual,"Token no valido" );
			}
			break;

		case 1:
			if ( Util::EsDigito( c ) || Util::EsLetra( c ) || c=='_' )
			{
				lexema+= Util::ToUpper(c);
				estado_automata = 1;
				codigo_fuente->Avanzar();
			}
			else
			{
				token.SetLexema( lexema );
				token.SetTipo( id );

				map<string,Token>::iterator it = palabras_reservadas.find( lexema );

				if ( it != palabras_reservadas.end() )
					return it->second;
				else
					return token;
			}
			break;

		case 2:
			token.SetTipo(op_suma);
			token.SetLexema(lexema);
			return token;

		case 3:
			if ( c != '*' )
			{
				if ( c == '\n' )
					linea_actual++;

				estado_automata =3;
				codigo_fuente->Avanzar();
			}
			else
			{
				estado_automata = 19;
				codigo_fuente->Avanzar();
			}
			break;

		case 4:
			token.SetLexema("EOF");
			token.SetTipo(eof);
			return token;

		case 5:
			if ( c == '/' )
			{
				estado_automata = 6;
				codigo_fuente->Avanzar();
			}
			else if ( c == '*' )
			{
				estado_automata = 3;
				codigo_fuente->Avanzar();
			}
			else
			{
				token.SetLexema( "/" );
				token.SetTipo( op_div );
				return token;
			}
			break;

		case 6:
			if ( c == '\n' )
			{
				linea_actual++;
				estado_automata = 0;
				codigo_fuente->Avanzar();
			}
			else
			{
				codigo_fuente->Avanzar();
				estado_automata = 6;
			}
			break;

		case 7:
			if ( Util::EsDigito( c ) )
			{
				estado_automata = 7;
				lexema+=c;
				codigo_fuente->Avanzar();
			}
			else if( c == '.' )
			{
				//lexema+=c;
				estado_automata = 15;
				codigo_fuente->Avanzar();
			}
			else if ( c== 'E' || c=='e' )
			{
				lexema+=c;
				estado_automata = 26;
				codigo_fuente->Avanzar();
			}
			else
			{
				token.SetLexema ( lexema );
				token.SetTipo(lit_int);
				return token;
			}
			break;

		case 8:
			if ( Util::EsOctalDig(c)  )
			{
				lexema+= c ;
				estado_automata = 9;
				codigo_fuente->Avanzar();
			}
			else if( c == '.' )
			{
				lexema+=c;
				estado_automata = 15;
				codigo_fuente->Avanzar();
			}
			else
			{
				token.SetLexema( lexema );
				token.SetTipo( lit_int );
				return token;
			}

			break;

		case 9:
			if ( Util::EsOctalDig(c) )
			{
				lexema+=c;
				estado_automata = 10;
				codigo_fuente->Avanzar();
			}
			else
			{
				token.SetLexema( lexema );
				token.SetTipo( lit_int );
				return token;
			}
			break;

		case 10:
			if( Util::EsOctalDig(c) )
			{
				lexema+=c;
				estado_automata = 11;
				codigo_fuente->Avanzar();
			}
			else
			{
				token.SetLexema(lexema);
				token.SetTipo( lit_int);
				return token;
			}
			break;

		case 11:
			token.SetLexema(lexema);
			token.SetTipo(lit_int);
			return token;
			
		case 12:
			if ( Util::EsHexDig( c ) )
			{
				lexema+=c;
				estado_automata=13;
				codigo_fuente->Avanzar();
			}
			else
				throw LexicalException(linea_actual,"Constante hexadecimal invalida");

			break;

		case 13:
			if ( Util::EsHexDig( c ) )
			{
				lexema+=c;
				estado_automata=14;
				codigo_fuente->Avanzar();
			}
			else
			{
				token.SetLexema(lexema);
				token.SetTipo(lit_int);
				return token;
			}
			break;

		case 14:
			token.SetLexema(lexema);
			token.SetTipo(lit_int);
			return token;

		case 15:
			if ( Util::EsDigito( c ) )
			{
				lexema+='.';
				lexema+=c;
				estado_automata = 16;
				codigo_fuente->Avanzar();
			}
			else if ( c == '.' )
			{
				//lexema+=c;
				codigo_fuente->Retroceder();
				token.SetLexema( lexema );
				token.SetTipo( lit_int );
				return token;
			}
			else
			{
				lexema+='.';
				token.SetLexema( lexema );
				token.SetTipo( lit_float );
				return token;
			}
			break;

		case 16:
			if ( Util::EsDigito( c ) )
			{
				lexema+=c;
				estado_automata = 16;
				codigo_fuente->Avanzar();
			}
			else if ( c=='E' || c=='e' )
			{
				lexema+=c;
				estado_automata = 26;
				codigo_fuente->Avanzar();
			}
			else
			{
				token.SetLexema(lexema);
				token.SetTipo(lit_float);
				return token;
			}

			break;

		case 17:
			if ( c != '\'' )
			{
				lexema+=c;
				longitud_cadenas++;
				estado_automata =17;
				codigo_fuente->Avanzar();
			}
			else
			{
				lexema+=c;
				estado_automata = 18;
				codigo_fuente->Avanzar();
			}
			break;

		case 18:
			if ( c == '\'' )
			{
				longitud_cadenas++;
				estado_automata = 17;
				codigo_fuente->Avanzar();
			}
			else
			{
				if ( longitud_cadenas <= 1)
					token.SetTipo(lit_caracter);
				else
					token.SetTipo( lit_string);
				token.SetLexema(lexema);
				
				return token;
			}
			
			break;
		case 19:
			if ( c != '/' )
			{
				estado_automata = 3;
				codigo_fuente->Avanzar();
			}
			else
			{
				estado_automata = 0;
				codigo_fuente->Avanzar();
			}
			break;

		case 20:
			if ( c == '=' )
			{
				lexema+=c;
				estado_automata =21;
				codigo_fuente->Avanzar();
			}
			else
			{
				token.SetLexema( lexema );
				token.SetTipo( op_mayorque );
				return token;
			}
			break;

		case 21:
			token.SetLexema( lexema );
			token.SetTipo( op_mayorigual);
			return token;

		case 22:
			if ( lexema.compare("[")==0 )
			{
				token.SetTipo(punt_corchizq);
			}
			else if (lexema.compare("]")==0 )
			{
				token.SetTipo( punt_corchder);
			}
			else if ( lexema.compare("(")==0 )
			{
				token.SetTipo(punt_parentizq);
			}
			else if (lexema.compare(")")==0 )
			{
				token.SetTipo(punt_parentder);
			}
			else if ( lexema.compare("{")==0 )
			{
				token.SetTipo(punt_llaveizq);
			}
			else if (lexema.compare("}")==0 )
			{
				token.SetTipo(punt_llaveder);
			}
			else if( lexema.compare(";")==0 )
			{
				token.SetTipo(punt_puntocoma);
			}
			else if ( lexema.compare(",")==0 )
			{
				token.SetTipo(punt_coma);
			}

				token.SetLexema(lexema);
				return token;

		case 23:
				if ( c == '=' )
			{
				lexema+=c;
				codigo_fuente->Avanzar();
				token.SetLexema(lexema);
				token.SetTipo(op_asignacion);
				return token;
			}
			else
			{
				token.SetLexema(lexema);
				token.SetTipo(punt_colon);
				return token;
			}
				break;


		case 24:
			if( c == '.' )
			{
				lexema+=c;
				estado_automata = 25;
				codigo_fuente->Avanzar();

			}
			else if ( Util::EsDigito( c ) )
			{
				lexema+=c;
				estado_automata = 16;
				codigo_fuente->Avanzar();
			}
			else
			{
				token.SetLexema(lexema);
				token.SetTipo(punt_punto);
				return token;
			}
			break;
		case 25:
			token.SetLexema(lexema);
			token.SetTipo(punt_doblepunto);
			return token;

		case 26:
			if ( c == '+' || c== '-' )
			{
				lexema+=c;
				estado_automata = 27;
				codigo_fuente->Avanzar();
			}
			else if ( Util::EsDigito( c ) ) 
			{
				lexema+=c;
				estado_automata = 28;
				codigo_fuente->Avanzar();
			}
			else
			{
				throw LexicalException(linea_actual,"Token de punto flotante invalido" );
			}
			break;
		case 27:
			if ( Util::EsDigito( c ) )
			{
				lexema+=c;
				estado_automata=28;
				codigo_fuente->Avanzar();
			}
			else
				throw LexicalException(linea_actual,"Token de punto flotante invalido" );
			break;
			
		case 28:
			if ( Util::EsDigito( c ) )
			{
				lexema+=c;
				estado_automata = 28;
				codigo_fuente->Avanzar();
			}
			else
			{
				token.SetLexema(lexema);
				token.SetTipo( lit_float );
				return token;
			}
			break;

		case 29:
			if ( c == '>' )
			{
				lexema+=c;
				estado_automata =30;
				codigo_fuente->Avanzar();
			}
			else
			{
				throw LexicalException(linea_actual,"Token invalido");
			}
			break;

		case 30:
			token.SetLexema(lexema);
			token.SetTipo(punt_delimpascalder);
			modo_html = true;
			return token;

		case 31:
			if ( c == '%' )
			{
				lexema+=c;
				estado_automata = 32;
				codigo_fuente->Avanzar();
			}
			else if ( c=='=')
			{
				lexema+=c;
				codigo_fuente->Avanzar();
				token.SetLexema(lexema);
				token.SetTipo(op_menorigual);
				return token;
			}
			else if( c=='>' )
			{
				lexema+=c;
				codigo_fuente->Avanzar();
				token.SetLexema(lexema);
				token.SetTipo(op_distinto);
				return token;
			}
			else
			{
				token.SetLexema(lexema);
				token.SetTipo(op_menorque);
				return token;
			}
			break;

		case 32:
			token.SetLexema(lexema);
			token.SetTipo(punt_delimpascalizq);
			modo_html = false;
			return token;
				
		default:
			break;
		}//Fin switch
		
	}
}

Token Lexico::ObtenerSiguienteTokenHTML()
{
	
	Token token;
	string lexema;
	char c;
	int estado_automata = 0;

	while ( true )
	{
		c = codigo_fuente->LeerCaracter();

		switch ( estado_automata )
		{
			
		case 0:
			if ( c==' ' || c== '\t' )
			{
				estado_automata = 0;
				codigo_fuente->Avanzar();
			}
			else if ( c == '\n' )
			{
				estado_automata = 0;
				linea_actual++;
				codigo_fuente->Avanzar();
			}
			else if ( c == EOF )
			{
				token.SetLexema("EOF");
				token.SetTipo(eof);
				return token;
			}
			else
			{
				estado_automata = 1;
			}
			break;
			
		case 1:
			if ( c != '<' && c != EOF )
			{
				if ( c == '\n' )
					linea_actual++;

				lexema+=c;
				estado_automata = 1;
				codigo_fuente->Avanzar();
			}
			else if ( c == EOF )
			{
				token.SetLexema(lexema);
				token.SetTipo(html);
				return token;
			}
			else if( c == '<' )
			{
				estado_automata = 2;
				codigo_fuente->Avanzar();
			}
			break;

		case 2:
			if ( c == '%' )
			{
				token.SetLexema(lexema);
				token.SetTipo(html);
				codigo_fuente->Retroceder();
				modo_html = false;
				return token;
			}
			else
			{
				if ( c == '\n' )
					linea_actual++;

				lexema+='<';
				lexema+=c;
				estado_automata = 1;
				codigo_fuente->Avanzar();
			}
		}//FIN switch
		
	}
}

unsigned int Lexico::GetLineaActual()
{
	return linea_actual;
}