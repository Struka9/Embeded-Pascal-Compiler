#pragma once
enum tipo_qualifier{qt_index,qt_campo};
class Qualifier
{
public:
	virtual tipo_qualifier GetTipo()=0;
};

