#pragma once

class Hora
{
public:
	Hora() {};
	Hora(int hora, int minuts, int segons) 
	{ 
		this->hora = hora; 
		this->minuts = minuts;
		this->segons = segons;
	}
	Hora(const Hora& toCopy)
	{
		hora = toCopy.getHora();
		minuts = toCopy.getMinuts();
		segons = toCopy.getSegons();
	}
	~Hora();

	bool horaValida();
	int toSeconds() const;
	void fromSeconds(int segons);

	int getHora() const;
	int getMinuts() const;
	int getSegons() const;
	void setHora(int hora) { this->hora = hora; }
	void setMinuts(int minuts) { this->minuts = minuts; }
	void setSegons(int segons) { this->segons = segons; }

	bool operator==(const Hora& h);
	bool operator<(const Hora& h);
	Hora operator+(const Hora& h);
	Hora operator+(int segons);
private:
	int hora;
	int minuts;
	int segons;
};
