#pragma once
#include <string>
using namespace std;

enum tipo_token{error=-1,eof,keyword,id,
	op_suma,op_resta,op_mul,op_div,op_divent,op_asignacion,op_mayorque,op_mayorigual,op_menorque,op_menorigual,op_igual,op_distinto,op_mod,op_and,
	punt_corchder,punt_corchizq,punt_parentder,punt_parentizq,punt_llaveder,punt_llaveizq,punt_puntocoma,punt_coma,punt_colon,punt_punto,punt_doblepunto,punt_delimpascalder,punt_delimpascalizq,
	lit_int,lit_float,lit_string,lit_caracter,lit_boolean,
	kw_write,kw_read,kw_program,kw_tipo,kw_array,kw_of,kw_record,kw_end,kw_var,kw_procedimiento,kw_funcion,kw_begin,kw_while,kw_repeat,kw_for,kw_if,kw_case,kw_else,kw_do,kw_to,kw_downto,kw_then,kw_until,kw_not,kw_or,kw_entero,kw_real,kw_string,kw_bool,kw_char,
	html};

class Token
{
private:
	int linea;
	string lexema;
	tipo_token tipo;

public:
	Token();
	~Token();
	void SetTipo(tipo_token tipo);
	void SetLexema(string lexema);
	void SetLineaAparicion(int linea);
	tipo_token GetTipo();
	string GetLexema(); 
	int GetLineaAparicion();

};

