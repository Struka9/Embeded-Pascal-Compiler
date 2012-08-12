#pragma once
#include "Sentencia.h"
#include "Suma.h"
#include "ConstanteEntera.h"
#include "Resta.h"
#include "SentenciaAsignacion.h"
#include "Identificador.h"
#include <string>
using namespace std;

enum direccion{ascendente,descendente};

class SentenciaFor :
	public Sentencia
{
private:
	Identificador* id;
	Expresion* inicializacion;
	direccion dir;
	Expresion* condicion;
	Sentencia* codigo;
	void Interpretar();

public:
	SentenciaFor(Identificador* id, Expresion* inicializacion, direccion dir, 
		Expresion* condicion, Sentencia* codigo  );
	~SentenciaFor(void);

	void SetId(Identificador* id);
	void SetInicializacion(Expresion* expr);
	void SetDir( direccion dir);
	void SetCondicion(Expresion* condicion);
	void SetCodigo(Sentencia* stmt);

	Identificador* GetId();
	Expresion* GetInicializacion();
	direccion GetDir();
	Expresion* GetCondicion();
	Sentencia* GetCodigo();
	void validarSemantica();


};

