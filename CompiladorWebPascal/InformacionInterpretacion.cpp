#include "InformacionInterpretacion.h"

InformacionInterpretacion* InformacionInterpretacion::instancia = NULL;

InformacionInterpretacion::InformacionInterpretacion()
{
	SetContexto("@GLOBAL");
}


InformacionInterpretacion::~InformacionInterpretacion()
{
}

InformacionInterpretacion* InformacionInterpretacion::GetInstance()
{
	if ( instancia == NULL )
		instancia = new InformacionInterpretacion();

	return instancia;
}

Valor* InformacionInterpretacion::GetFromTablaValores(string id)
{
	map<string,ListaValores*>::iterator it = tabla_contexto.find(contexto);
	ListaValores* l_vals = it->second;

	Valor* val = l_vals->ObtenerValor(id);

	if ( contexto.compare("@GLOBAL") != 0 && val == NULL )
	{
		it = tabla_contexto.find("@GLOBAL");
		l_vals = it->second;

		return l_vals->ObtenerValor(id);
	}

	return val;
}

void InformacionInterpretacion::InsertarEnTablaValores(string id, Valor* val)
{
	 
	ListaValores* l_vals = tabla_contexto.find(contexto)->second;
	Valor* buscar_valor = l_vals->ObtenerValor(id);
	if ( contexto.compare("@GLOBAL") != 0 && buscar_valor == NULL )
	{
		l_vals= tabla_contexto.find("@GLOBAL")->second; 
		l_vals->Insertar(id,val);
		tabla_contexto["@GLOBAL"] = l_vals;
	}
	else
	{
		l_vals->Insertar(id,val);
		tabla_contexto[contexto] = l_vals ;
	}
	//tabla_contexto.insert(pair<string,ListaValores*>(contexto,l_vals) );
	
}

void InformacionInterpretacion::SetContexto(string contexto)
{
	this->contexto = contexto;
}

void InformacionInterpretacion::InicializarVariables(string nom_contexto, ListaVariables* vars)
{
	//ListaVariables* tabla_simbolos_de_contexto = InformacionSemantica::GetInstance()->GetTablaSimbolos();
	ListaVariables* tabla_simbolos_de_contexto = vars;
	list<string> ids = tabla_simbolos_de_contexto->GetNombreCampos();

	if( ids.size() == 0 )
		return;

	list<string>::iterator it = ids.begin();
	ListaValores* nueva_lista_vals = new ListaValores();

	for ( ; it != ids.end() ; it++ )
	{
			Valor* t_val;
			Tipo* tipo = tabla_simbolos_de_contexto->get( (*it) );
			switch ( tipo->GetTipo() )
			{
			case t_entero:
				t_val = new ValorEntero();
				break;
		
			case t_real:
				t_val = new ValorReal();
				break;

			case t_boolean:
				t_val = new ValorBooleano();
				break;

			case t_cadena:
				t_val = new ValorCadena();
				break;

			case t_caracter:
				t_val = new ValorCaracter();
				break;

			case t_registro:
					t_val = new ValorRegistro( (Registro*)tipo );
					break;

			case t_arreglo:
				t_val = new ValorArreglo( (Arreglo*)tipo);
				break;

			default:
				throw std::exception("Tipo no soportado");

			}

			nueva_lista_vals->Insertar((*it),t_val);
			//GetInstance()->InsertarEnTablaValores((*it),t_val);

	}

	tabla_contexto.insert(pair<string,ListaValores*>(nom_contexto,nueva_lista_vals) );

}

void InformacionInterpretacion::InsertarValorEnContexto(string contexto,string id, Valor* v)
{

	ListaValores* lista = tabla_contexto.find( contexto )->second;

	lista->Insertar(id,v);

	tabla_contexto[contexto] = lista;
}

Valor* InformacionInterpretacion::clone(Valor* v)
{
	tipo_valor tipo_v = v->GetTipoValor();
	Valor* ret = NULL;

	if ( tipo_v == entero )
	{
		ValorEntero* original = (ValorEntero*)v;
		ValorEntero* v_entero = new ValorEntero();
		memcpy(v_entero,original,sizeof(ValorEntero) );
		ret = v_entero;
	}
	else if ( tipo_v == real )
	{
		ValorReal* original = (ValorReal*)v;
		ValorReal* v_real =  new ValorReal();
		memcpy(v_real,original,sizeof(ValorReal) );
		ret = v_real;
	}
	else if ( tipo_v == caracter )
	{
		ValorCaracter* original = (ValorCaracter*)v;
		ValorCaracter* v_char = new ValorCaracter();
		memcpy(v_char,original,sizeof(ValorCaracter) );
		ret = v_char;
	}
	else if ( tipo_v == cadena )
	{
		ValorCadena* original = (ValorCadena*)v;
		ValorCadena* v_cad = new ValorCadena();
		memcpy( v_cad,original,sizeof(ValorCadena) );
		ret = v_cad;
	}
	else if( tipo_v == boolean)
	{
		ValorBooleano* original = (ValorBooleano*)v;
		ValorBooleano* v_bool = new ValorBooleano();
		memcpy(v_bool,original,sizeof(ValorBooleano) );
		ret = v_bool;
	}
	else if( tipo_v == arreglo )
	{
		ValorArreglo* original = (ValorArreglo*)v;
		ValorArreglo* v_arr = new ValorArreglo();
		memcpy(v_arr,original,sizeof( ValorArreglo ) );
		ret = v_arr;
	}
	else if ( tipo_v == registro )
	{
		ValorRegistro* original = (ValorRegistro*)v;
		ValorRegistro* v_reg = new ValorRegistro();
		memcpy(v_reg,original,sizeof( ValorRegistro) );
		ret = v_reg;
	}

	return ret;
}