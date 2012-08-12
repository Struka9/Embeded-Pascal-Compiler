#pragma once
#include "InformacionSemantica.h"
#include "Parametro.h"
#include "DefNodosExpresion.h"
#include "DefNodosSentencia.h"
#include "Clausula.h"
#include "LimitesRango.h"
#include "ClausulaCase.h"
#include "SyntaxException.h"
#include "SemanticException.h"
#include "Lexico.h"
#include "DeclaracionVariable.h"
#include "ListaVariables.h"
#include "Tipo.h"

#include <string>
using namespace std;

class Sintactico
{
private:
	string nombre_archivo;
	Token proximo_token;
	Lexico *analizador_lexico;

	Sentencia* ParseS();
	Sentencia* ParseProgram();
	void ParseProgramHeader();
	Sentencia* ParseProgramContent();
	void ParseTypeDefinitions();
	ListaVariables* ParseVariableDeclarations();
	list<DeclaracionFuncion*> ParseFunctionDeclarations(); //falta la implementacion
	list<DeclaracionFuncion*> ParseFunctionDeclarationList();
	list<DeclaracionFuncion*> _ParseFunctionDeclarationList();
	DeclaracionFuncion* ParseFunctionDeclaration();
	list<Parametro*> ParseProcedureParam();
	list<Parametro*> ParseFunctionParam();
	void ParseTypeDefinitionList();
	void ParseTypeDefinition();
	void _ParseTypeDefinitionList();
	Tipo* ParseType();
	list<LimitesRango*> ParseDimensionList();
	list<LimitesRango*> _ParseDimensionList();	
	ListaVariables* ParseVariableDeclarationList(); 
	ListaVariables* _ParseVariableDeclarationList();
	DeclaracionVariable* ParseVariableDeclaration();
	list<string> ParseIdentifierList();
	list<string> _ParseIdentifierList();
	list<Parametro*> ParseParameterList();
	Parametro* ParseParameter();
	list<Parametro*> _ParseParameterList();
	bool ParseParameterReference();

	string ParseFieldName();
	Qualifier* ParseFieldSpecifier();
	list<Expresion*> ParseFunctionCall();
	//void ParseParams();
	Qualifier* ParseIndex();
	list<Expresion*> ParseIndexList();
	list<Expresion*> _ParseIndexList();
	void ParseMemberGroup();
	void _ParseMemberGroup();
	void ParseMemberList();
	void _ParseMemberList();

	list<Qualifier*> ParseQualifiers();
	list<Qualifier*> ParseQualifierList();
	list<Qualifier*> _ParseQualifierList();
	Qualifier* ParseQualifier();

	void ParseVariableReference();
	Expresion* ParseTerm();
	Expresion* _ParseTerm(Expresion* her);
	//Sentencias
	direccion ParseDirection();
	Sentencia* ParseStatement();
	Sentencia* ParseWhileStatement();
	Sentencia* ParseRepeatStatement();
	Sentencia* ParseElseStatement();
	Sentencia* ParseIfStatement();
	Sentencia* ParseForStatement();
	Sentencia* ParseCompoundStatement();
	Sentencia* ParseWriteStatement();
	Sentencia* ParseReadStatement();
	LimitesRango* ParseRange(int inferior);
	list<ClausulaCase*> ParseCaseClauseList();
	list<ClausulaCase*> _ParseCaseClauseList();
	Sentencia* ParseDefaultCaseClause();
	Sentencia* ParseStatementList();
	Sentencia* _ParseStatementList();
	Sentencia* ParseUnlabeledStatement();
	Sentencia* ParseSimpleStatement();
	Sentencia* ParseStructuredStatement();
	Sentencia* ParseIterationStatement();
	Sentencia* ParseSelectionStatement();
	Sentencia* ParseAssignmentStatement(string nombre_id);
	Sentencia* ParseCaseStatement();
	Sentencia* ParseProcedureStatement(string nombre_procedimiento);

	//Expresiones
	Expresion* ParseExpression();
	Expresion* ParseFactor();
	Expresion* ParseUnaryExpression();
	list<Expresion*> ParseArgumentList();
	list<Expresion*> _ParseArgumentList();
	Expresion* ParseRelationalExpression();
	Expresion* _ParseRelationalExpression(Expresion* expr1);
	Expresion* ParseSimpleExpression();
	Expresion* _ParseSimpleExpression(Expresion* her);

	//constantes
	tipo_token ParseUnaryOperator();
	tipo_token ParseAdditiveOperator();
	tipo_token ParseMultiplicativeOperator();
	tipo_token ParseRelationalOperator();
	void ParseIdentifiers();
	Expresion* ParseLiteralConstant();

public:
	Sintactico(string nombre_archivo);
	~Sintactico(void);
	Sentencia* GenerarArbol();
};

