#pragma once
class LimitesRango
{
private:
	int inferior,superior;
public:
	LimitesRango(int inferior,int superior);
	~LimitesRango(void);

	void SetInferior(int inf);
	void SetSuperior(int sup);

	int GetSuperior();
	int GetInferior();

	int GetCant();

};

