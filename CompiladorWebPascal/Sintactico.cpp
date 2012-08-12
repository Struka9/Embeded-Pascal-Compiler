#include "Sintactico.h"

//PENDIENTE Dar soporte a char y bool
Sintactico::Sintactico(string nombre_archivo)
{
	analizador_lexico = 0;
	this->nombre_archivo = nombre_archivo;
}


Sintactico::~Sintactico(void)
{
	delete analizador_lexico;
}

Sentencia* Sintactico::GenerarArbol()
{
	analizador_lexico = new Lexico(nombre_archivo);
	//Inicializacion del token
	proximo_token = analizador_lexico->ObtenerSiguienteToken();
	return ParseS();
}

Sentencia* Sintactico::ParseS()
{
	Sentencia* stmt = ParseProgram();
	if( proximo_token.GetTipo() !=eof )
		throw SyntaxException("se esperaba fin de archivo",analizador_lexico->GetLineaActual() );
	return stmt;

}

Sentencia* Sintactico::ParseProgram()
{
	ParseProgramHeader();
	return ParseProgramContent();	
}

void Sintactico::ParseProgramHeader()
{

	if ( proximo_token.GetTipo() == punt_delimpascalizq )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();

		ParseTypeDefinitions();
		ListaVariables* lista_vars = ParseVariableDeclarations();
		InformacionInterpretacion::GetInstance()->InicializarVariables("@GLOBAL",lista_vars);
		list<DeclaracionFuncion*> lista_funcs = ParseFunctionDeclarations();
		list<DeclaracionFuncion*>::iterator it = lista_funcs.begin();

		for ( ; it != lista_funcs.end() ; it++ )
		{
			InformacionSemantica::GetInstance()->InsertarEnTablaDeFunciones( (*it)->GetNombre() , (*it) );
			(*it)->ValidarSemantica();
		}

		InformacionSemantica::GetInstance()->SetContexto("@GLOBAL");
		InformacionInterpretacion::GetInstance()->SetContexto("@GLOBAL");
		if ( proximo_token.GetTipo() == punt_delimpascalder )
			proximo_token = analizador_lexico->ObtenerSiguienteToken();
		else
			throw SyntaxException("No se encontro el token delimitador %>",analizador_lexico->GetLineaActual());

	}

}

void Sintactico::ParseTypeDefinitions()
{

	if ( proximo_token.GetTipo() == kw_tipo )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();
		ParseTypeDefinitionList();	
	}
}

ListaVariables* Sintactico::ParseVariableDeclarations()
{
	ListaVariables* vars_declaradas = new ListaVariables();
	if ( proximo_token.GetTipo() == kw_var )
	{
	    proximo_token = analizador_lexico->ObtenerSiguienteToken();
		vars_declaradas = ParseVariableDeclarationList();
		InformacionSemantica::GetInstance()->SetTablaSimbolos( vars_declaradas );
	}
	return vars_declaradas;
}

list<DeclaracionFuncion*> Sintactico::ParseFunctionDeclarations()
{
	list<DeclaracionFuncion*> lista;
	//Utilizamos el conjunto Primeros( FunctionDeclarationList )
	if ( proximo_token.GetTipo() == kw_procedimiento || proximo_token.GetTipo() == kw_funcion )
	{
		lista =  ParseFunctionDeclarationList();
	}
	return lista;
}

void Sintactico::ParseTypeDefinitionList()
{
	ParseTypeDefinition();
	_ParseTypeDefinitionList();
}

void Sintactico::_ParseTypeDefinitionList()
{
	//Utilizamos PRIMERO ( TypeDefinitionList )
	if ( proximo_token.GetTipo() == id )
	{
		ParseTypeDefinition();
		_ParseTypeDefinitionList();
	}

}

void Sintactico::ParseTypeDefinition()
{

	if ( proximo_token.GetTipo() == id )
	{
		string nom_id = proximo_token.GetLexema();

		proximo_token = analizador_lexico->ObtenerSiguienteToken();

		if ( proximo_token.GetTipo() == op_igual )
		{
			proximo_token = analizador_lexico->ObtenerSiguienteToken();

			Tipo* t = ParseType();

			if ( proximo_token.GetTipo() == punt_puntocoma )
				proximo_token = analizador_lexico->ObtenerSiguienteToken();
			else
				throw SyntaxException("No se encontro el token de punto y coma",analizador_lexico->GetLineaActual() );

			InformacionSemantica::GetInstance()->InsertarEnTablaTipos(nom_id,t);

		}
		else 
			throw SyntaxException("No se encontro el token de operador de asignacion",analizador_lexico->GetLineaActual() );
	} 
	else
		throw SyntaxException("No se encontro un id valido",analizador_lexico->GetLineaActual());
}

Tipo* Sintactico::ParseType()
{
	switch ( proximo_token.GetTipo() )
	{
	case id:
		{
			
			string nom_tipo = proximo_token.GetLexema();
			proximo_token = analizador_lexico->ObtenerSiguienteToken();
			map<string,Tipo*>tablaTipos = InformacionSemantica::GetInstance()->GetTablaTipos();
			map<string,Tipo*>::iterator it;
			it = tablaTipos.find(nom_tipo);

			if ( it == tablaTipos.end() )
				throw SemanticException("El tipo " +nom_tipo+" no esta definido");
			return it->second;
		}
		
	case kw_array:
		proximo_token = analizador_lexico->ObtenerSiguienteToken();
		if ( proximo_token.GetTipo() == punt_corchizq )
		{
			proximo_token = analizador_lexico->ObtenerSiguienteToken();
			list<LimitesRango*> dim_list = ParseDimensionList();

			if ( proximo_token.GetTipo() == punt_corchder )
			{
				proximo_token = analizador_lexico->ObtenerSiguienteToken();

				if ( proximo_token.GetTipo() == kw_of )
				{
					proximo_token = analizador_lexico->ObtenerSiguienteToken();
					Tipo* t = ParseType();

					return new Arreglo(dim_list,t);
				}
				else
					throw SyntaxException("No se encontro la kw OF",analizador_lexico->GetLineaActual());

			}
			else
				throw SyntaxException("No se encontro el token de corchete derecho",analizador_lexico->GetLineaActual());
		}
		else
			throw SyntaxException("No se encontro el token de corchete izquierdo",analizador_lexico->GetLineaActual());
		break;

	case kw_record:
		{
			proximo_token = analizador_lexico->ObtenerSiguienteToken();
			ListaVariables* lista_var = ParseVariableDeclarationList();

			if ( proximo_token.GetTipo() == kw_end )
				proximo_token = analizador_lexico->ObtenerSiguienteToken();
			else
				throw SyntaxException("No se encontro la kw END",analizador_lexico->GetLineaActual());

			return new Registro(lista_var);
		}

	case kw_entero:
		{
			proximo_token = analizador_lexico->ObtenerSiguienteToken();
			map<string,Tipo*>tablaTipos = InformacionSemantica::GetInstance()->GetTablaTipos();
			map<string,Tipo*>::iterator it;
			it = tablaTipos.find("INTEGER");
			return it->second;
		}

	case kw_real:
		{
			proximo_token = analizador_lexico->ObtenerSiguienteToken();
			map<string,Tipo*>tablaTipos = InformacionSemantica::GetInstance()->GetTablaTipos();
			map<string,Tipo*>::iterator it;
			it = tablaTipos.find("REAL");
			return it->second;
		}

	case kw_string:
		{
			proximo_token = analizador_lexico->ObtenerSiguienteToken();
			map<string,Tipo*>tablaTipos = InformacionSemantica::GetInstance()->GetTablaTipos();
			map<string,Tipo*>::iterator it;
			it = tablaTipos.find("STRING");
			return it->second;
		}

	case kw_bool:
		{
			proximo_token = analizador_lexico->ObtenerSiguienteToken();
			map<string,Tipo*>tablaTipos = InformacionSemantica::GetInstance()->GetTablaTipos();
			map<string,Tipo*>::iterator it;
			it = tablaTipos.find("BOOLEAN");
			return it->second;
		}

	case kw_char:
		{
			proximo_token = analizador_lexico->ObtenerSiguienteToken();
			map<string,Tipo*>tablaTipos = InformacionSemantica::GetInstance()->GetTablaTipos();
			map<string,Tipo*>::iterator it;
			it = tablaTipos.find("CHAR");
			return it->second;
		}
	default:
		throw SyntaxException("Token de tipo invalido",analizador_lexico->GetLineaActual());

	}//FIN switch
}

list<LimitesRango*> Sintactico::ParseDimensionList()
{
	if ( proximo_token.GetTipo() == lit_int )
	{
		int inf = atoi(proximo_token.GetLexema().c_str());

		proximo_token = analizador_lexico->ObtenerSiguienteToken();
		
		if ( proximo_token.GetTipo() == punt_doblepunto )
		{
			proximo_token = analizador_lexico->ObtenerSiguienteToken();

			if ( proximo_token.GetTipo() == lit_int )
			{
				int sup = atoi( proximo_token.GetLexema().c_str() );

				if ( inf > sup )
					throw SemanticException("El indice inferior del arreglo debe ser menor o igual al superior");

				proximo_token = analizador_lexico->ObtenerSiguienteToken();
				list<LimitesRango*> lista_dim = _ParseDimensionList();
				list<LimitesRango*>::iterator it = lista_dim.begin();
				lista_dim.insert(it,new LimitesRango(inf,sup) );
				return lista_dim;
			}
			else
				throw SyntaxException("No se encontro una constante entera",analizador_lexico->GetLineaActual());
		}
		else 
			throw SyntaxException("No se encontro el token de doble punto",analizador_lexico->GetLineaActual());
	}
	else
		throw SyntaxException("No se encontro una constante entera",analizador_lexico->GetLineaActual());
}

list<LimitesRango*> Sintactico::_ParseDimensionList()
{
	list<LimitesRango*> lista_dim;

	if ( proximo_token.GetTipo() == punt_coma )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();
		if ( proximo_token.GetTipo() == lit_int )
		{
			int inf = atoi( proximo_token.GetLexema().c_str() );

			proximo_token = analizador_lexico->ObtenerSiguienteToken();
		
			if ( proximo_token.GetTipo() == punt_doblepunto )
			{
				proximo_token = analizador_lexico->ObtenerSiguienteToken();

				if ( proximo_token.GetTipo() == lit_int )
				{
					int sup = atoi( proximo_token.GetLexema().c_str() );

					if ( inf > sup )
						throw SemanticException("El indice inferior del arreglo debe ser menor o igual al superior");
					proximo_token = analizador_lexico->ObtenerSiguienteToken();

					lista_dim = _ParseDimensionList();

					list<LimitesRango*>::iterator it = lista_dim.begin();
					lista_dim.insert(it,new LimitesRango(inf,sup) );
				}
				else
					throw SyntaxException("No se encontro una constante entera",analizador_lexico->GetLineaActual());
			}
			else 
				throw SyntaxException("No se encontro el token de doble punto",analizador_lexico->GetLineaActual());
		}
		else
			throw SyntaxException("No se encontro una constante entera",analizador_lexico->GetLineaActual());
	}

	return lista_dim;
}

ListaVariables* Sintactico::ParseVariableDeclarationList()
{
	DeclaracionVariable* decl_var = ParseVariableDeclaration();
	ListaVariables* lista_var = _ParseVariableDeclarationList();
	
	list<string> ids = decl_var->GetIds();
	list<string>::iterator it;
	for ( it = ids.begin() ; it != ids.end() ; it++)
	{
		lista_var->insert((*it),decl_var->GetTipo() );
	}
	
	return lista_var;
}

ListaVariables* Sintactico::_ParseVariableDeclarationList()
{
	ListaVariables* lista_var = new ListaVariables();
	//Utilizamos Primero( VariableDeclarationList )
	if ( proximo_token.GetTipo() == id )
	{
		DeclaracionVariable* decl_var = ParseVariableDeclaration();
	    lista_var = _ParseVariableDeclarationList();

		list<string> ids = decl_var->GetIds();
		list<string>::iterator it;
		for ( it = ids.begin() ; it != ids.end() ; it++)
		{
			lista_var->insert((*it),decl_var->GetTipo() );
		}
	}

	return lista_var;

}

DeclaracionVariable* Sintactico::ParseVariableDeclaration()
{
	list<string> ids = ParseIdentifierList();

	if ( proximo_token.GetTipo() == punt_colon )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();

		Tipo* t = ParseType();
		if ( proximo_token.GetTipo() == punt_puntocoma )
			proximo_token = analizador_lexico->ObtenerSiguienteToken();
		else
			throw SyntaxException("No se encontro el token de punto y coma",analizador_lexico->GetLineaActual());
		
		DeclaracionVariable* decl =  new DeclaracionVariable(ids,t);
		return decl;
	}
	else
		throw SyntaxException("No se encontro el token colon",analizador_lexico->GetLineaActual());
}

void Sintactico::ParseIdentifiers()
{
	//Utilizamos Primeros ( IdentifierList )
	if ( proximo_token.GetTipo() == id )
	{
		ParseIdentifierList();
	}
}

list<string> Sintactico::ParseIdentifierList()
{
	if ( proximo_token.GetTipo() == id )
	{
		string nom_id = proximo_token.GetLexema();

		proximo_token = analizador_lexico->ObtenerSiguienteToken();
		list<string> lista_ids = _ParseIdentifierList();
		list<string>::iterator it = lista_ids.begin();

		lista_ids.insert(it,nom_id);
		return lista_ids;
	}
	else
		throw SyntaxException("No se encontro un id valido",analizador_lexico->GetLineaActual());
}

list<string> Sintactico::_ParseIdentifierList()
{
	list<string> lista_ids;
	if( proximo_token.GetTipo() == punt_coma )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();
		if ( proximo_token.GetTipo() == id )
		{
			string nom_id = proximo_token.GetLexema();

			proximo_token = analizador_lexico->ObtenerSiguienteToken();
			lista_ids = _ParseIdentifierList();
			list<string>::iterator it = lista_ids.begin();

			lista_ids.insert(it,nom_id);
		}
		else
			throw SyntaxException("No se encontro un token de id",analizador_lexico->GetLineaActual() );
	}

	return lista_ids;
}

list<DeclaracionFuncion*> Sintactico::ParseFunctionDeclarationList()
{
	list<DeclaracionFuncion*> lista_funciones;
	DeclaracionFuncion* func_decl = ParseFunctionDeclaration();
	lista_funciones = _ParseFunctionDeclarationList();

	list<DeclaracionFuncion*>::iterator it = lista_funciones.begin();
	lista_funciones.insert(it,func_decl);

	return lista_funciones;
}

list<DeclaracionFuncion*> Sintactico::_ParseFunctionDeclarationList()
{
	list<DeclaracionFuncion*> lista_funciones;
	//Utilizamos Primero( FunctionDeclarationList )
	if ( proximo_token.GetTipo() == kw_procedimiento || proximo_token.GetTipo() == kw_funcion )
	{
		DeclaracionFuncion* func_decl = ParseFunctionDeclaration();
		lista_funciones = _ParseFunctionDeclarationList();
		list<DeclaracionFuncion*>::iterator it = lista_funciones.begin();

		lista_funciones.insert(it,func_decl);
	}

	return lista_funciones;
}

DeclaracionFuncion* Sintactico::ParseFunctionDeclaration()
{
	if ( proximo_token.GetTipo() == kw_procedimiento )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();

		if ( proximo_token.GetTipo() == id )
		{
			string nom_procedimiento = proximo_token.GetLexema();
			proximo_token = analizador_lexico->ObtenerSiguienteToken();

			InformacionSemantica::GetInstance()->SetContexto(nom_procedimiento);
			InformacionInterpretacion::GetInstance()->SetContexto(nom_procedimiento);

			list<Parametro*> lista_params = ParseProcedureParam();
			ListaVariables* lista_vars = ParseVariableDeclarations();

			Sentencia* cuerpo_funcion = ParseCompoundStatement();

			//PENDIENTE: Verificar si es correcto

			
			list<Parametro*>::iterator it = lista_params.begin();

			for ( ; it != lista_params.end() ; it++ )
			{
				lista_vars->insert((*it)->GetNombre(),(*it)->GetTipo() );
			}

			InformacionInterpretacion::GetInstance()->InicializarVariables(nom_procedimiento,lista_vars);
			return new DeclaracionFuncion(nom_procedimiento,lista_params,cuerpo_funcion,NULL);
		}
		else
			throw SyntaxException("No se encontro un id valido",analizador_lexico->GetLineaActual());
	}
	else if ( proximo_token.GetTipo() == kw_funcion )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();
		if ( proximo_token.GetTipo() == id )
		{
			string nom_funcion = proximo_token.GetLexema();
			proximo_token = analizador_lexico->ObtenerSiguienteToken();

			list<Parametro*>lista_params = ParseFunctionParam();
			Tipo* t = ParseType();

			if ( proximo_token.GetTipo() == punt_puntocoma )
			{
				proximo_token = analizador_lexico->ObtenerSiguienteToken();
				InformacionSemantica::GetInstance()->SetContexto( nom_funcion );
				InformacionInterpretacion::GetInstance()->SetContexto(nom_funcion);
				ListaVariables* lista_vars = ParseVariableDeclarations();


				Sentencia* cuerpo_funcion = ParseCompoundStatement();

				list<Parametro*>::iterator it = lista_params.begin();
				
				for ( ; it != lista_params.end() ; it++ )
				{
					lista_vars->insert((*it)->GetNombre(),(*it)->GetTipo() );
				}

				InformacionSemantica::GetInstance()->InsertarVarEnContexto(nom_funcion,nom_funcion,t);

				//lista_vars->insert(nom_funcion,t);
				InformacionInterpretacion::GetInstance()->InicializarVariables(nom_funcion,lista_vars);
				return new DeclaracionFuncion(nom_funcion,lista_params,cuerpo_funcion,t);
			}
			else
				throw SyntaxException("Falta un punto y coma",analizador_lexico->GetLineaActual());
		}
		else
			throw SyntaxException("Falta el id",analizador_lexico->GetLineaActual());
	}
	else
		throw SyntaxException("Se esperaba una declaracion de funcion o procedimiento",analizador_lexico->GetLineaActual());

	//InformacionInterpretacion::GetInstance()->SetContexto("@GLOBAL");
}

list<Parametro*> Sintactico::ParseProcedureParam()
{
	list<Parametro*> lista_params;
	if ( proximo_token.GetTipo() == punt_puntocoma )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();
		return lista_params;
	}
	else if ( proximo_token.GetTipo() == punt_parentizq )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();

		lista_params = ParseParameterList();
		if ( proximo_token.GetTipo() == punt_parentder )
		{
			proximo_token = analizador_lexico->ObtenerSiguienteToken();

			if ( proximo_token.GetTipo() == punt_puntocoma )
			{
				proximo_token = analizador_lexico->ObtenerSiguienteToken();
				return lista_params;
			}
			else
				throw SyntaxException("Falta un punto y coma",analizador_lexico->GetLineaActual());
		}
		else{

			throw SyntaxException("Falta un parentesis derecho",analizador_lexico->GetLineaActual());
		}
	}else 
		throw SyntaxException("Parametro de procedimiento incorrecto",analizador_lexico->GetLineaActual());
}

list<Parametro*> Sintactico::ParseFunctionParam()
{
	list<Parametro*> lista_params;
	if ( proximo_token.GetTipo() == punt_colon )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();
		return lista_params; //Lista de parametros vacia

	}
	else if ( proximo_token.GetTipo() == punt_parentizq )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();

		lista_params = ParseParameterList();

		if (proximo_token.GetTipo() == punt_parentder)
		{
			proximo_token = analizador_lexico->ObtenerSiguienteToken();

			if ( proximo_token.GetTipo() == punt_colon )
			{
				proximo_token = analizador_lexico->ObtenerSiguienteToken();
				return lista_params;
			}
			else
				throw SyntaxException("Falta un token de colon" ,analizador_lexico->GetLineaActual());
		}
		else
			throw SyntaxException("Falta un parentesis derecho",analizador_lexico->GetLineaActual());
	}
	else 
		throw SyntaxException("Token invalido",analizador_lexico->GetLineaActual());
}

list<Parametro*> Sintactico::ParseParameterList()
{
	list<Parametro*> lista_params;
	list<Parametro*>::iterator it;
	Parametro* parametro = ParseParameter();
	lista_params = _ParseParameterList();
	
	it = lista_params.begin();
	lista_params.insert(it,parametro);

	return lista_params;
}

list<Parametro*> Sintactico::_ParseParameterList()
{
	list<Parametro*> lista_params;
	if ( proximo_token.GetTipo() == punt_coma )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();

		Parametro* parametro = ParseParameter();
		lista_params = _ParseParameterList();

		list<Parametro*>::iterator it = lista_params.begin();
		lista_params.insert(it,parametro);
	}
	return lista_params;
}

Parametro* Sintactico::ParseParameter()
{
	bool esPorReferencia = ParseParameterReference();
	if ( proximo_token.GetTipo() == id )
	{
			string identificador = proximo_token.GetLexema();

			proximo_token =  analizador_lexico->ObtenerSiguienteToken();

			if ( proximo_token.GetTipo() == punt_colon )
			{
				proximo_token = analizador_lexico->ObtenerSiguienteToken();

				Tipo* t = ParseType();

				return new Parametro(identificador,esPorReferencia,t);
			}
			else 
				throw SyntaxException("se esperaba un token de dos puntos",analizador_lexico->GetLineaActual() );
	}
	else if ( esPorReferencia && proximo_token.GetTipo() != id )
		throw SyntaxException("se esperaba un id valido",analizador_lexico->GetLineaActual() );

}

bool Sintactico::ParseParameterReference()
{
	if ( proximo_token.GetTipo() == kw_var )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();

		return true;
	}

	return false;
}

Sentencia* Sintactico::ParseProgramContent()
{
	if ( proximo_token.GetTipo() == html )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();

		return ParseProgramContent();
	}
	else if ( proximo_token.GetTipo() == punt_delimpascalizq )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();
		Sentencia* stmt = ParseStatementList();
		//Sentencia* stmt = ParseStatement();

		if (proximo_token.GetTipo() == punt_delimpascalder )
		{
			proximo_token = analizador_lexico->ObtenerSiguienteToken();
			Sentencia* p_content = ParseProgramContent();

			stmt->SetSiguiente( p_content );

			return stmt;
		}
		else
			throw SyntaxException("Falta el delimitador %>",analizador_lexico->GetLineaActual());
	}
	else
		return 0;
	
}

Sentencia* Sintactico::ParseStatementList()
{
	Sentencia* stmt = ParseStatement();
	Sentencia* stmt_list = _ParseStatementList();

	stmt->SetSiguiente(stmt_list);

	ListaSentencias* lista = new ListaSentencias(stmt);
	return lista;
}

Sentencia* Sintactico::ParseStatement()
{
	//Utilizamos Primeros
	if ( proximo_token.GetTipo() == id || proximo_token.GetTipo() == kw_begin || 
		proximo_token.GetTipo() == kw_while || proximo_token.GetTipo() == kw_repeat || proximo_token.GetTipo() == kw_for ||
		proximo_token.GetTipo() == kw_if || proximo_token.GetTipo() == kw_case || proximo_token.GetTipo() == kw_write || proximo_token.GetTipo()==kw_read )
	{
		return ParseUnlabeledStatement();
	}

	return 0;
}

Sentencia* Sintactico::_ParseStatementList()
{
	//Utilizamos Primeros
	if ( proximo_token.GetTipo() == id || proximo_token.GetTipo() == kw_begin || 
		proximo_token.GetTipo() == kw_while || proximo_token.GetTipo() == kw_repeat || proximo_token.GetTipo() == kw_for ||
		proximo_token.GetTipo() == kw_if || proximo_token.GetTipo() == kw_case || proximo_token.GetTipo() == kw_write || proximo_token.GetTipo() == kw_read )
	{
		Sentencia* stmt = ParseStatement();
		Sentencia* stmt_list = _ParseStatementList();

		stmt->SetSiguiente(stmt_list);
		ListaSentencias* lista = new ListaSentencias(stmt);
		return lista;
	}

	return 0;
}

Sentencia* Sintactico::ParseUnlabeledStatement()
{
	//Utilizamos Primeros
	if ( proximo_token.GetTipo() == id || proximo_token.GetTipo()== kw_write || proximo_token.GetTipo() == kw_read )
	{
		return ParseSimpleStatement();
	}
	else if ( proximo_token.GetTipo() == kw_begin || 
		proximo_token.GetTipo() == kw_while || proximo_token.GetTipo() == kw_repeat || proximo_token.GetTipo() == kw_for ||
		proximo_token.GetTipo() == kw_if || proximo_token.GetTipo() == kw_case )
	{
		return ParseStructuredStatement();
	}
	else
		throw SyntaxException("Sentencia Incorrecta",analizador_lexico->GetLineaActual());
}

Sentencia* Sintactico::ParseSimpleStatement()
{
	if ( proximo_token.GetTipo() == id )
	{
		string identificador = proximo_token.GetLexema();

		proximo_token = analizador_lexico->ObtenerSiguienteToken();

		if ( proximo_token.GetTipo() == punt_puntocoma || proximo_token.GetTipo() == punt_parentizq )
		{
			return ParseProcedureStatement(identificador);

		}
		else if ( proximo_token.GetTipo() == op_asignacion || proximo_token.GetTipo() == punt_punto ||
			proximo_token.GetTipo() == punt_corchizq )
		{
			 return ParseAssignmentStatement(identificador);
		}
		else
			throw SyntaxException("Token no valido",analizador_lexico->GetLineaActual() );
	}
	else if (proximo_token.GetTipo() == kw_write)
	{
		return ParseWriteStatement();
	}
	else if (proximo_token.GetTipo() == kw_read )
	{
		return ParseReadStatement();
	}
	else
		throw SyntaxException("Sentencia invalida",analizador_lexico->GetLineaActual());
}

Sentencia* Sintactico::ParseStructuredStatement()
{
	//Utilizamos Primeros
	if ( proximo_token.GetTipo() == kw_begin )
	{
		return ParseCompoundStatement();
	}
	else if ( proximo_token.GetTipo() == kw_while || proximo_token.GetTipo() == kw_for || proximo_token.GetTipo() == kw_repeat )
	{
		return ParseIterationStatement();
	}
	else if ( proximo_token.GetTipo() == kw_if || proximo_token.GetTipo() == kw_case )
	{
		return ParseSelectionStatement();
	}
	else
		throw SyntaxException("Error de sentencia",analizador_lexico->GetLineaActual());

}

Sentencia* Sintactico::ParseIterationStatement()
{
	//Utilizamos Primeros
	if ( proximo_token.GetTipo() == kw_for )
	{
		return ParseForStatement();
	}
	else if ( proximo_token.GetTipo() == kw_repeat )
	{
		return ParseRepeatStatement();
	}
	else if ( proximo_token.GetTipo() == kw_while )
	{
		return ParseWhileStatement();
	}
	else
		throw SyntaxException("No se encontro token valido",analizador_lexico->GetLineaActual() );
}

Sentencia* Sintactico::ParseSelectionStatement()
{
	//Utilizamos Primeros

	if ( proximo_token.GetTipo() == kw_if )
	{
		return ParseIfStatement();
	}
	else if ( proximo_token.GetTipo() == kw_case )
	{
		return ParseCaseStatement();
	}
	return 0;
}

Sentencia* Sintactico::ParseAssignmentStatement(string nombre_id)
{
		list<Qualifier*> qualifier_list = ParseQualifiers();

		if ( proximo_token.GetTipo() == op_asignacion )
		{
			proximo_token = analizador_lexico->ObtenerSiguienteToken();

			Expresion* expr = ParseExpression();

			if ( proximo_token.GetTipo() == punt_puntocoma )
				proximo_token = analizador_lexico->ObtenerSiguienteToken();
			else
				throw SyntaxException("Falta un punto y coma",analizador_lexico->GetLineaActual());

			Identificador* identificador = new Identificador(nombre_id,qualifier_list);

			return new SentenciaAsignacion(identificador,expr);
		}
		else
			throw SyntaxException("no se encontro el operador de asignacion",analizador_lexico->GetLineaActual());
	
}

Sentencia* Sintactico::ParseProcedureStatement(string nombre_procedimiento )
{
	if ( proximo_token.GetTipo() == punt_puntocoma)
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();

		list<Expresion*> lista_vacia;
		FunctionCall* llamada_proc = new FunctionCall(nombre_procedimiento,lista_vacia);
		return new SentenciaProcedimiento(llamada_proc);
	}
	else 
		if ( proximo_token.GetTipo() == punt_parentizq )
		{
			proximo_token = analizador_lexico->ObtenerSiguienteToken();
			list<Expresion*> args = ParseArgumentList();

			if ( proximo_token.GetTipo() == punt_parentder )
			{
				proximo_token = analizador_lexico->ObtenerSiguienteToken();

				if (proximo_token.GetTipo() == punt_puntocoma )
					proximo_token = analizador_lexico->ObtenerSiguienteToken();
				else
					throw SyntaxException("Falta un punto y coma",analizador_lexico->GetLineaActual() );
			}
			else
				throw SyntaxException("Falta un parentesis derecho", analizador_lexico->GetLineaActual() );

			FunctionCall* llamada_proc = new FunctionCall(nombre_procedimiento,args);
			return new SentenciaProcedimiento(llamada_proc);
		}
		else throw SyntaxException("Token no valido ",analizador_lexico->GetLineaActual() );
}

Sentencia* Sintactico::ParseCaseStatement()
{
	if ( proximo_token.GetTipo() == kw_case )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();
		Expresion* evaluacion = ParseExpression();

		if ( proximo_token.GetTipo() == kw_of )
		{
			proximo_token = analizador_lexico->ObtenerSiguienteToken();	
			list<ClausulaCase*> lista_clausulas = ParseCaseClauseList();
			Sentencia* default_stmt = ParseDefaultCaseClause();
			

			if(proximo_token.GetTipo() == kw_end )
				proximo_token = analizador_lexico->ObtenerSiguienteToken();
			else
				throw SyntaxException("Falta la palabra clave end",analizador_lexico->GetLineaActual());

			return new SentenciaCase(evaluacion,lista_clausulas,default_stmt);
		}
		else
			throw SyntaxException("Falta la palabra clave of",analizador_lexico->GetLineaActual());
	}
	else
		throw SyntaxException("Error falta la palabra clave CASE",analizador_lexico->GetLineaActual());
}


list<ClausulaCase*> Sintactico::ParseCaseClauseList()
{
	list<ClausulaCase*>lista_clausulas;
	//Utilizamos Primero
	if ( proximo_token.GetTipo() == lit_int || proximo_token.GetTipo()== lit_float || proximo_token.GetTipo()== lit_string || proximo_token.GetTipo()==lit_caracter )
	{
		ConstanteLiteral* lit_const  =(ConstanteLiteral*) ParseLiteralConstant();

		if ( proximo_token.GetTipo() == punt_colon )
		{
			proximo_token = analizador_lexico->ObtenerSiguienteToken();

			Sentencia* stmt = ParseStatement();
			ClausulaCase* clausula = new ClausulaCase(lit_const,stmt);

			lista_clausulas = _ParseCaseClauseList();
			list<ClausulaCase*>::iterator it = lista_clausulas.begin();
			lista_clausulas.insert(it,clausula);
			return lista_clausulas;
		}
		else throw SyntaxException("Se esperaba un token de dos puntos",analizador_lexico->GetLineaActual() );
		
	}
	return lista_clausulas;
}


list<ClausulaCase*> Sintactico::_ParseCaseClauseList()
{
	list<ClausulaCase*> lista_clausulas;
	if ( proximo_token.GetTipo() == punt_puntocoma )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();

		ConstanteLiteral* const_lit = (ConstanteLiteral*)ParseLiteralConstant();

		if ( proximo_token.GetTipo() == punt_colon)
		{
			proximo_token = analizador_lexico->ObtenerSiguienteToken();

			Sentencia* stmt = ParseStatement();
			ClausulaCase* clausula = new ClausulaCase(const_lit,stmt);

			lista_clausulas = _ParseCaseClauseList();
			list<ClausulaCase*>::iterator it = lista_clausulas.begin();
			lista_clausulas.insert(it,clausula);

			return lista_clausulas;
		}
		else throw SyntaxException("Se espera un token de dos puntos",analizador_lexico->GetLineaActual() );
	}
	return lista_clausulas;
}


LimitesRango* Sintactico::ParseRange(int inferior)
{
	if ( proximo_token.GetTipo() == punt_doblepunto )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();

		if ( proximo_token.GetTipo() == lit_int )
		{
			string sup = proximo_token.GetLexema();
			proximo_token = analizador_lexico->ObtenerSiguienteToken();

			LimitesRango* lim = new LimitesRango( inferior, atoi( sup.c_str() ) );
			return lim;
		}
		else
			throw SyntaxException("Se esperaba un literal entero",analizador_lexico->GetLineaActual() );
	}

	return new LimitesRango(inferior,inferior);
}

Sentencia* Sintactico::ParseDefaultCaseClause()
{
		if ( proximo_token.GetTipo() == kw_else )
		{
			proximo_token = analizador_lexico->ObtenerSiguienteToken();

			return ParseStatement();
		}
		return 0;
}

Sentencia* Sintactico::ParseCompoundStatement()
{
	if (proximo_token.GetTipo() == kw_begin )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();
		Sentencia* stmt  = ParseStatementList();

		if ( proximo_token.GetTipo() == kw_end )
			proximo_token = analizador_lexico->ObtenerSiguienteToken();
		else
			throw SyntaxException("Error falta la palabra clave END",analizador_lexico->GetLineaActual());

		return stmt;
	}
	else
		throw SyntaxException("Falta la palabra clave begin",analizador_lexico->GetLineaActual());
}

Sentencia* Sintactico::ParseForStatement()
{
	if ( proximo_token.GetTipo() == kw_for )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();

		if ( proximo_token.GetTipo() == id )
		{
			string id = proximo_token.GetLexema();

			proximo_token = analizador_lexico->ObtenerSiguienteToken();

			if ( proximo_token.GetTipo() == op_asignacion )
			{
				proximo_token = analizador_lexico->ObtenerSiguienteToken();

				Expresion* inicializacion = ParseExpression();
				direccion dir = ParseDirection();
				Expresion* condicion = ParseExpression();

				if ( proximo_token.GetTipo() == kw_do )
				{
					proximo_token = analizador_lexico->ObtenerSiguienteToken();

					Sentencia* codigo = ParseStatement();
					list<Qualifier*> lista_vacia;
					Identificador* identificador = new Identificador(id,lista_vacia) ;
					return new SentenciaFor(identificador,inicializacion,dir,condicion,codigo);
				}
				else
					throw SyntaxException("Falta kw do: produccion for",analizador_lexico->GetLineaActual());

			}
			else
				throw SyntaxException("Falta un operador de asignacion: prodccion for",analizador_lexico->GetLineaActual());
		}
		else
			throw SyntaxException("Falta un id: produccion for statement",analizador_lexico->GetLineaActual());
	}
	else
		throw SyntaxException("Falta la kw FOR",analizador_lexico->GetLineaActual());
}

direccion Sintactico::ParseDirection()
{
	if ( proximo_token.GetTipo() == kw_to )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();

		return ascendente;
	}
	else if ( proximo_token.GetTipo() == kw_downto )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();

		return descendente;
	}
	else
		throw SyntaxException("Falta la palabra clave to o downto" ,analizador_lexico->GetLineaActual() );

}

Sentencia* Sintactico::ParseIfStatement()
{
	if ( proximo_token.GetTipo() == kw_if )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();

		Expresion* expr = ParseExpression();

		if ( proximo_token.GetTipo() == kw_then )
		{
			proximo_token = analizador_lexico->ObtenerSiguienteToken();
			Sentencia* stmt = ParseStatement();
			Sentencia* elseStmt = ParseElseStatement();

			return new SentenciaIf(expr,stmt,elseStmt);
		}
		else
			throw SyntaxException("Falta kw then: produccion if statement",analizador_lexico->GetLineaActual());
	}
	else
		throw SyntaxException( "Falta kw if: produccion if statement",analizador_lexico->GetLineaActual());
}

Sentencia* Sintactico::ParseElseStatement()
{
	if ( proximo_token.GetTipo() == kw_else )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();

		Sentencia* else_stmt = ParseStatement();

		if ( else_stmt == 0 )
			throw SyntaxException("Cuerpo de sentencia else vacio, puede haber ambiguedad",analizador_lexico->GetLineaActual() );

		return else_stmt;
	}
	else
		return 0;
}

Sentencia* Sintactico::ParseRepeatStatement()
{
	if ( proximo_token.GetTipo() == kw_repeat )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();

		Sentencia* stmt = ParseStatementList();

		if ( proximo_token.GetTipo() == kw_until )
		{
			proximo_token = analizador_lexico->ObtenerSiguienteToken();

			Expresion* expr = ParseExpression();

			if ( proximo_token.GetTipo() == punt_puntocoma )
				proximo_token = analizador_lexico->ObtenerSiguienteToken();
			else
				throw SyntaxException("Falta un punto y coma, sentencia repeat",analizador_lexico->GetLineaActual() );

			return new SentenciaRepeat(stmt,expr);
		}
		else
			throw SyntaxException("Falta la kw until: produccion RepeatStatement",analizador_lexico->GetLineaActual());
	}
	else
		throw SyntaxException("Falta la kw repeat: produccion Repeat Statement",analizador_lexico->GetLineaActual());
}

Sentencia* Sintactico::ParseWhileStatement()
{
	if ( proximo_token.GetTipo() == kw_while )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();

		Expresion* expr = ParseExpression();

		if ( proximo_token.GetTipo() == kw_do )
		{
			proximo_token = analizador_lexico->ObtenerSiguienteToken();

			Sentencia* stmt = ParseStatement();

			return new SentenciaWhile(expr,stmt);
		}
		else
			throw SyntaxException("Falta kw do",analizador_lexico->GetLineaActual());
	}
	else
		throw SyntaxException("Falta kw while: produccion WhileStatement",analizador_lexico->GetLineaActual());
}

Expresion* Sintactico::ParseExpression()
{
	return ParseRelationalExpression();
}

list<Expresion*> Sintactico::ParseArgumentList()
{
	list<Expresion*> argument_list;
	if( proximo_token.GetTipo() != punt_parentder )
	{
		Expresion* expr = ParseExpression();
		argument_list = _ParseArgumentList();
		list<Expresion*>::iterator it = argument_list.begin();
		argument_list.insert(it,expr);

	}
	return argument_list;

}

list<Expresion*> Sintactico::_ParseArgumentList()
{
	list<Expresion*> expr_list;
	if ( proximo_token.GetTipo() == punt_coma )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();
		Expresion* expr = ParseExpression();
		expr_list = _ParseArgumentList();

		list<Expresion*>::iterator it = expr_list.begin();
		expr_list.insert(it,expr);
	}
	return expr_list;
}

Expresion* Sintactico::ParseFactor()
{
	
	if ( proximo_token.GetTipo() == punt_parentizq )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();
		Expresion* expr = ParseExpression();

		if ( proximo_token.GetTipo() == punt_parentder )
		{
			proximo_token = analizador_lexico->ObtenerSiguienteToken();
		}
		else
			throw SyntaxException("Falta un parentesis derecho: produccion Factor",analizador_lexico->GetLineaActual());

		return expr;
	}
	else if ( proximo_token.GetTipo() == lit_int || proximo_token.GetTipo() == lit_float || proximo_token.GetTipo() == lit_string || proximo_token.GetTipo() == lit_boolean || proximo_token.GetTipo() == lit_caracter )
	{
		return ParseLiteralConstant();
	}
	else if ( proximo_token.GetTipo() == op_suma || proximo_token.GetTipo() == op_resta || proximo_token.GetTipo() == kw_not )
	{
		//Utilizamos Primeros ( unary-expression )
		return ParseUnaryExpression();
	}
	else if ( proximo_token.GetTipo() == id )
	{
		string identificador = proximo_token.GetLexema();

		proximo_token = analizador_lexico->ObtenerSiguienteToken();

		if ( proximo_token.GetTipo() == punt_parentizq )
		{

			list<Expresion*>args = ParseFunctionCall();
			FunctionCall* func = new FunctionCall(identificador,args);
			return func;

		}
		else
		{
			 list<Qualifier*> qualifier_list = ParseQualifiers();
			 Identificador* id = new Identificador(identificador,qualifier_list);
			 return id;
		}
	}
	else
		throw SyntaxException("No se encontro un token correcto...factor",analizador_lexico->GetLineaActual() );
}

string Sintactico::ParseFieldName()
{
	if ( proximo_token.GetTipo() == id )
	{
		string field_name = proximo_token.GetLexema();
		proximo_token = analizador_lexico->ObtenerSiguienteToken();
		return field_name;
	}
	else
		throw SyntaxException("Falta id produccion FieldName",analizador_lexico->GetLineaActual());
}

Qualifier* Sintactico::ParseFieldSpecifier()
{
	if ( proximo_token.GetTipo() == punt_punto )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();

		string field_name = ParseFieldName();

		return new Referencia(field_name);
	}
	else
		throw SyntaxException("Falta punto: produccion FieldSpecifier",analizador_lexico->GetLineaActual());
}

list<Expresion*> Sintactico::ParseFunctionCall()
{
	if ( proximo_token.GetTipo() == punt_parentizq )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();
		
		list<Expresion*> argument_list = ParseArgumentList();

		if( proximo_token.GetTipo() == punt_parentder )
			proximo_token = analizador_lexico->ObtenerSiguienteToken();
		else
			throw SyntaxException("Falta un parentesis derecho, produccion Params",analizador_lexico->GetLineaActual());

		return argument_list;
	}
	else
		throw SyntaxException("Se esperaba un token de parentesis izquierdo",analizador_lexico->GetLineaActual());
}

Qualifier* Sintactico::ParseIndex()
{
	if ( proximo_token.GetTipo() == punt_corchizq )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();

		list<Expresion*>expression_list = ParseIndexList();

		if ( proximo_token.GetTipo() == punt_corchder )
			proximo_token = analizador_lexico->ObtenerSiguienteToken();
		else
			throw SyntaxException("Falta corchete derecho: produccion Index",analizador_lexico->GetLineaActual());

		return new Indexacion(expression_list);
	}
	else
		throw SyntaxException("Falta un corchete izq: producccion Index",analizador_lexico->GetLineaActual());
}

list<Expresion*> Sintactico::ParseIndexList()
{
	Expresion* expr = ParseExpression();
	list<Expresion*> expression_list = _ParseIndexList();
	list<Expresion*>::iterator it = expression_list.begin();
	expression_list.insert(it,expr);
	return expression_list;
}

list<Expresion*> Sintactico::_ParseIndexList()
{
	list<Expresion*>expression_list;
	if ( proximo_token.GetTipo() == punt_coma )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();

		Expresion* expr = ParseExpression();
		 expression_list = _ParseIndexList();
		list<Expresion*>::iterator it = expression_list.begin();
		expression_list.insert(it,expr);
		return expression_list;
	}
	return expression_list;
}


void Sintactico::ParseMemberGroup()
{
	ParseExpression();
	_ParseMemberGroup();
}

void Sintactico::_ParseMemberGroup()
{
	if ( proximo_token.GetTipo() == punt_doblepunto )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();
		ParseExpression();
	}
}

void Sintactico::ParseMemberList()
{
	ParseMemberGroup();
	_ParseMemberList();
}

void Sintactico::_ParseMemberList()
{
	if ( proximo_token.GetTipo() == punt_coma )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();

		ParseMemberGroup();
		_ParseMemberList();
	}
}

list<Qualifier*> Sintactico::ParseQualifiers()
{
	//De no haber qualifiers se retornara una lista de cero elementos
	list<Qualifier*> qualifier_list ;
	//Utilizamos primeros( qualifier-list )
	if ( proximo_token.GetTipo() == punt_punto || proximo_token.GetTipo() == punt_corchizq )
	{
		qualifier_list = ParseQualifierList();
	}
	return qualifier_list;
}

list<Qualifier*> Sintactico::ParseQualifierList()
{

	Qualifier* qualifier = ParseQualifier();
	list<Qualifier*>qualifier_list = _ParseQualifierList();
	list<Qualifier*>::iterator it = qualifier_list.begin();
	qualifier_list.insert(it,qualifier);
	return qualifier_list;
}

list<Qualifier*> Sintactico::_ParseQualifierList()
{
	list<Qualifier*> qualifier_list;
	//Utilizamos Primeros( qualifier )
	if ( proximo_token.GetTipo() == punt_punto || proximo_token.GetTipo() == punt_corchizq )
	{
		Qualifier* qualifier = ParseQualifier();
		qualifier_list = _ParseQualifierList();
		list<Qualifier*>::iterator it = qualifier_list.begin();
		qualifier_list.insert(it,qualifier);
	}

	return qualifier_list;
}

Qualifier* Sintactico::ParseQualifier()
{
	//Utilizamos Primeros(field-specifier) y Primeros( index )
	if ( proximo_token.GetTipo() == punt_punto )
	{
		return ParseFieldSpecifier();
	}
	else if ( proximo_token.GetTipo() == punt_corchizq )
	{
		return ParseIndex();
	}
	else throw SyntaxException("Falta token de cualificador",analizador_lexico->GetLineaActual() );
}

Expresion* Sintactico::ParseRelationalExpression()
{
	Expresion* expr1 = ParseSimpleExpression();
	return _ParseRelationalExpression(expr1);
}

Expresion* Sintactico::_ParseRelationalExpression(Expresion* expr1)
{
	//Utilizamos Primeros( Relational-Operator )
	if ( proximo_token.GetTipo() == op_igual || proximo_token.GetTipo() == op_distinto || proximo_token.GetTipo() == op_menorque ||
		proximo_token.GetTipo() == op_mayorque || proximo_token.GetTipo() == op_menorigual || proximo_token.GetTipo() == op_mayorigual )
	{
		tipo_token op = ParseRelationalOperator();
		Expresion* expr2 = ParseSimpleExpression();

		switch ( op )
		{
		case op_igual:
			 return new ExprIgualQue(expr1,expr2);

		case op_distinto:
			return new ExprDistinto(expr1,expr2);

		case op_menorque:
			return new ExprMenorQue(expr1,expr2);

		case op_mayorque:
			return new ExprMayorQue(expr1,expr2);

		case op_menorigual:
			return new ExprMenorIgual(expr1,expr2);

		case op_mayorigual:
			return new ExprMayorIgual(expr1,expr2);
		}

	}

	return expr1;
}

Expresion* Sintactico::ParseSimpleExpression()
{
	Expresion* expr = ParseTerm();
	return _ParseSimpleExpression(expr);
}

Expresion* Sintactico::_ParseSimpleExpression(Expresion* her)
{
	//Utilizamos Primeros(additive-operator)
	if ( proximo_token.GetTipo() == op_suma || proximo_token.GetTipo() == op_resta || proximo_token.GetTipo() == kw_or )
	{
		tipo_token tipo_adicion = ParseAdditiveOperator();
		Expresion* expr = ParseTerm();
		Expresion* sin;

		switch ( tipo_adicion )
		{

		case op_suma:
			sin = new Suma(her,expr);
			break;

		case op_resta:
			sin = new Resta(her,expr);
			break;

		case kw_or:
			sin = new OrBinario(her,expr);
			break;

		default:
			break;
		}

		return _ParseSimpleExpression(sin);
	}

	return her;
}

//PENDIENTE: Otra produccion que no se usa
void Sintactico::ParseVariableReference()
{
	if ( proximo_token.GetTipo() == id )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();
		ParseQualifierList();
	}
	else 
		throw SyntaxException("Falta un id: produccion Variable Reference",analizador_lexico->GetLineaActual());
}

Expresion* Sintactico::ParseTerm()
{
	Expresion* expr = ParseFactor();
	return _ParseTerm(expr);
}

Expresion* Sintactico::_ParseTerm(Expresion* her)
{
	//Utilizamos Primeros( multiplicative-operator )

	if ( proximo_token.GetTipo() == op_mul || proximo_token.GetTipo() == op_div || proximo_token.GetTipo() == op_divent || proximo_token.GetTipo() == op_mod ||
		proximo_token.GetTipo() == op_and )
	{
		tipo_token tipo_mul = ParseMultiplicativeOperator();
		Expresion* expr = ParseFactor();
		Expresion* sin;

		switch ( tipo_mul )
		{

		case op_mul:
			sin = new Multiplicacion(her,expr);
			break;

		case op_div:
			sin = new Division(her,expr);
			break;

		case op_divent:
			sin = new Division(her,expr);
			break;

		case op_mod:
			sin = new Modulo(her,expr);
			break;

		case op_and:
			sin = new AndBinario(her,expr);
			break;

		default:
			break;
		}

		return _ParseTerm(sin);
	}

	return her;
}

Expresion* Sintactico::ParseUnaryExpression()
{
	tipo_token op = ParseUnaryOperator();
	Expresion* expr = ParseFactor();

	switch ( op )
	{
	case op_suma:
		return new SumaUnaria(expr);
	case op_resta:
		return new RestaUnaria(expr);
	case kw_not:
		return new Negacion(expr);
	default:
		return 0;
	}
}

tipo_token Sintactico::ParseAdditiveOperator()
{
	if ( proximo_token.GetTipo() == op_suma || proximo_token.GetTipo() == op_resta || proximo_token.GetTipo() == kw_or )
	{
		tipo_token tipo = proximo_token.GetTipo();
		proximo_token = analizador_lexico->ObtenerSiguienteToken();
		return tipo;
	}
	else
		throw SyntaxException("Error falta un operador: produccion Additive Operator",analizador_lexico->GetLineaActual());
}

tipo_token Sintactico::ParseMultiplicativeOperator()
{
	if ( proximo_token.GetTipo() == op_mul || proximo_token.GetTipo() == op_div|| proximo_token.GetTipo() == op_divent || proximo_token.GetTipo() ==  op_mod ||
		proximo_token.GetTipo() == op_and )
	{
		tipo_token tipo = proximo_token.GetTipo();
		proximo_token = analizador_lexico->ObtenerSiguienteToken();

		return tipo;
	}
	else
		throw SyntaxException( "Falta operador mul: produccion Multiplicative Operator",analizador_lexico->GetLineaActual());
}

tipo_token Sintactico::ParseRelationalOperator()
{
	if ( proximo_token.GetTipo() == op_igual || proximo_token.GetTipo() == op_distinto || proximo_token.GetTipo() == op_menorque ||
		proximo_token.GetTipo() == op_mayorque || proximo_token.GetTipo() == op_menorigual || proximo_token.GetTipo() == op_mayorigual )
	{
		tipo_token tipo = proximo_token.GetTipo();

		proximo_token = analizador_lexico->ObtenerSiguienteToken();

		return tipo;
	}
	else
		throw SyntaxException("Falta operador relacional: Produccion relational operator", analizador_lexico->GetLineaActual());
	
}

tipo_token Sintactico::ParseUnaryOperator()
{
	if ( proximo_token.GetTipo() == op_suma || proximo_token.GetTipo() == op_resta || proximo_token.GetTipo() == kw_not )
	{
		tipo_token tipo = proximo_token.GetTipo();
		proximo_token = analizador_lexico->ObtenerSiguienteToken();

		return tipo;
	}
	else
		throw SyntaxException("Falta un operador: produccion Unary Operator",analizador_lexico->GetLineaActual());
}

Expresion* Sintactico::ParseLiteralConstant()
{
	Expresion* expr;

	if ( proximo_token.GetTipo() == lit_int )
		expr = new ConstanteEntera( atoi(proximo_token.GetLexema().c_str() ) );
	else if ( proximo_token.GetTipo() == lit_string )
	{
		string val =  proximo_token.GetLexema();
		string::iterator it = val.begin();
		val.erase(it);
		it=val.end()-1;
		val.erase(it);

		expr = new ConstanteString(val);
	}
	else if ( proximo_token.GetTipo() == lit_caracter )
	{
		string val = proximo_token.GetLexema();
		expr = new ConstanteCaracter(val);
	}
	else if( proximo_token.GetTipo() == lit_boolean)
	{
		string lexema = proximo_token.GetLexema();
		bool bVal;
		if ( lexema.compare("TRUE")==0 )
			bVal = true;
		else 
			bVal = false;

		expr = new ConstanteBooleana(bVal);
	}
	else if ( proximo_token.GetTipo() == lit_float )
		expr = new ConstanteReal( atof( proximo_token.GetLexema().c_str() ) );
	else
		throw SyntaxException("No se encontro una constante valida",analizador_lexico->GetLineaActual() );

	proximo_token = analizador_lexico->ObtenerSiguienteToken();
	return expr;
}

Sentencia* Sintactico::ParseWriteStatement()
{
	if ( proximo_token.GetTipo() == kw_write )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();

		Expresion* expr = ParseExpression();

		if ( proximo_token.GetTipo() == punt_puntocoma )
			proximo_token = analizador_lexico->ObtenerSiguienteToken();
		else
			throw SyntaxException("Falta un punto y coma", analizador_lexico->GetLineaActual() );

		return new SentenciaWrite(expr);
	}
	else
		throw SyntaxException("Se esperaba la palabra write",analizador_lexico->GetLineaActual() );
}


Sentencia* Sintactico::ParseReadStatement()
{
	if ( proximo_token.GetTipo() == kw_read )
	{
		proximo_token = analizador_lexico->ObtenerSiguienteToken();

		if ( proximo_token.GetTipo() == id )
		{
			string nom_id = proximo_token.GetLexema();

			proximo_token = analizador_lexico->ObtenerSiguienteToken();

			list<Qualifier*>lista_qualifiers = ParseQualifiers();

			if ( proximo_token.GetTipo() == punt_puntocoma )
				proximo_token = analizador_lexico->ObtenerSiguienteToken();
			else 
				throw SyntaxException("Se esperaba un punto y coma",analizador_lexico->GetLineaActual() );

			Identificador* id = new Identificador(nom_id,lista_qualifiers);
			return new SentenciaRead(id);
		}
		else
			throw SyntaxException("Se esperaba un id valido",analizador_lexico->GetLineaActual() );
	}
	else throw SyntaxException("Se esperaraba la palabra read",analizador_lexico->GetLineaActual() );
}