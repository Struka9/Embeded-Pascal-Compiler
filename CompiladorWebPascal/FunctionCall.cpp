#include "FunctionCall.h"


FunctionCall::FunctionCall(string function_name, list<Expresion*> arguments)
{
	SetFunctionName(function_name);
	SetArguments(arguments);
}


FunctionCall::~FunctionCall(void)
{
}

void FunctionCall::SetArguments(list<Expresion*> args)
{
	this->argument_list = args;
}

void FunctionCall::SetFunctionName(string func_name) 
{
	this->function_name = func_name;
}

list<Expresion*> FunctionCall::GetArguments()
{
	return argument_list;
}

string FunctionCall::GetFunctionName()
{
	return function_name;
}

Tipo* FunctionCall::validarSemantico()
{
	//Fue declarada la funcion?
	DeclaracionFuncion* func_decl = InformacionSemantica::GetInstance()->GetFromTablaFunciones(function_name);

	if ( func_decl == NULL )
		throw SemanticException("La funcion o procedimiento no ha sido declarado");

	list<Parametro*> lista_params = func_decl->GetParametros();

	//Tienen el mismo num de argumentos?
	if ( lista_params.size() != argument_list.size() )
		throw SemanticException("El numero de parametros de la llamada a funcion no concuerda con su declaracion");

	//Son los parametros de tipos equivalentes?
	list<Parametro*>::iterator decl_param_it = lista_params.begin();
	list<Expresion*>::iterator llamada_param_it = argument_list.begin();

	for (; decl_param_it != lista_params.end() ; decl_param_it++,llamada_param_it++ )
	{
		Tipo* tipo_decl_arg = (*decl_param_it)->GetTipo();
		Tipo* tipo_llamada_arg = (*llamada_param_it)->validarSemantico();

		if ( !tipo_decl_arg->EsEquivalente( tipo_llamada_arg ) )
			throw SemanticException("La expresion no es equivalente al tipo de parametro de la declaracion");
	}

	return func_decl->GetTipo();
}

Valor* FunctionCall::interpretar()
{
	InformacionInterpretacion::GetInstance()->SetContexto(function_name);
	InformacionSemantica::GetInstance()->SetContexto(function_name);

	DeclaracionFuncion* func_decl = InformacionSemantica::GetInstance()->GetFromTablaFunciones(function_name);
	
	//Colocarle el valor a los parametros
	list<Parametro*> parametros_func = func_decl->GetParametros();
	list<Parametro*>::iterator it_param = parametros_func.begin();
	list<Expresion*>::iterator it_expr = argument_list.begin();
	for ( ; it_param != parametros_func.end() ; it_param++,it_expr++)
	{
		string nom_param = (*it_param)->GetNombre();

		InformacionInterpretacion::GetInstance()->InsertarEnTablaValores( nom_param, (*it_expr)->interpretar() );
	}

	func_decl->GetCuerpoFuncion()->Interpretacion();

	for ( it_param = parametros_func.begin(),it_expr = argument_list.begin() ; it_param != parametros_func.end() ; it_param++, it_expr++)
	{
		bool esRef = (*it_param)->EsPorReferencia();
		
		if ( esRef )
		{
			Identificador* identificador = (Identificador*) (*it_expr);

			Valor* v_en_func = InformacionInterpretacion::GetInstance()->GetFromTablaValores( (*it_param)->GetNombre() );
			InformacionInterpretacion::GetInstance()->InsertarValorEnContexto( "@GLOBAL",identificador->GetId(),v_en_func );
		}
	}

	Valor* v_ret = InformacionInterpretacion::GetInstance()->GetFromTablaValores(function_name);

	InformacionInterpretacion::GetInstance()->SetContexto("@GLOBAL");
	InformacionSemantica::GetInstance()->SetContexto("@GLOBAL");

	return v_ret;
}