#include "Hora.h"

Hora::~Hora()
{
}

bool Hora::horaValida()
{
	return (
		hora >= 00 && hora < 24
		&& minuts >= 00 && minuts < 60
		&& segons >= 00 && segons < 60
	);
}

int Hora::toSeconds() const
{
	return segons + 60 * (minuts + 60*hora);
}

void Hora::fromSeconds(int segons)
{
	int newSeg = segons % 60;

	int newMin;
	if (segons >= 60)
		newMin = segons / 60;
	else
		newMin = 0;

	int newHor;
	if (newMin >= 60)
	{
		newHor = newMin / 60;
		newMin = newMin % 60;

		if (newHor >= 24)
		{
			newHor -= 24 * (newHor / 24);
		}
	}
	else
	{
		newHor = 0;
	}

	this->segons = newSeg;
	this->minuts = newMin;
	this->hora = newHor;
}

int Hora::getHora() const
{
	return hora;
}

int Hora::getMinuts() const
{
	return minuts;
}

int Hora::getSegons() const
{
	return segons;
}

bool Hora::operator==(const Hora & h)
{
	return (
		hora == h.getHora()
		&& minuts == h.getMinuts()
		&& segons == h.getSegons()
	);
}

bool Hora::operator<(const Hora & h)
{
	return toSeconds() < h.toSeconds();
}

Hora Hora::operator+(const Hora & h)
{
	int total = toSeconds() + h.toSeconds();
	fromSeconds(total);
	return *this;
}

Hora Hora::operator+(int segons)
{
	int total = toSeconds() + segons;
	fromSeconds(total);
	return *this;
}
