#include "Map.h"
#include "Persona.h"
#include <iostream>
#include <string>
#include <time.h>
using namespace std;


void mostraFitxer(const string& nomFitxer)
{
	ifstream fitxer;
	fitxer.open(nomFitxer);
	if (fitxer.is_open())
	{
		string linia;
		getline(fitxer, linia);
		while (!fitxer.eof())
		{
			cout << linia << endl;
			getline(fitxer, linia);
		}
		fitxer.close();
	}
}

bool igualFitxers(string nomF1, string nomF2)
{
	ifstream f1, f2;
	f1.open(nomF1);
	f2.open(nomF2);
	bool iguals = true;

	if (f1.is_open() && f2.is_open())
	{
		int linia = 0;
		while (!f1.eof() && !f2.eof())
		{
			++linia;
			string a, b;
			getline(f1, a);
			int pos;
			if ((pos = a.find_first_of(char(13))) < string::npos)
				a = a.substr(0, pos);
			getline(f2, b);
			if ((pos = b.find_first_of(char(13))) < string::npos)
				b = b.substr(0, pos);
			if (a != b)
				iguals = false;
		}
		if (!f1.eof() && f2.eof())
			iguals = false;
		if (!f2.eof() && f1.eof())
			iguals = false;
		f1.close();
		f2.close();
	}
	else
	{
		throw "Error al fitxer de sortida al comparar.";
	}
	return iguals;
}


int main()
{
	bool valid = true;
	float reduccio = 0.0;
	float grade = 0.0;
	cout << endl << "Grade :=>> " << grade << endl << endl;

	const int N_PROVES_CERCA = 6;
	const int N_PROVES_AFEGIR = 11;
	const int LONGITUD_VECTOR_PERSONA = 10;

	string clauStringTest[N_PROVES_AFEGIR] = { "NOM_G", "NOM_B", "NOM_J", "NOM_A", "NOM_D", "NOM_I", "NOM_F", "NOM_C","NOM_E", "NOM_H", "NOM_E" };
	Persona personaTest[N_PROVES_AFEGIR] = { 
		{ "NOM_G", 70 }, 
		{ "NOM_B", 20 }, 
		{ "NOM_J", 100 },
		{ "NOM_A", 10 },
		{ "NOM_D", 40 }, 
		{ "NOM_I", 90 },
		{ "NOM_F", 60 },
		{ "NOM_C", 30 },
		{ "NOM_E", 20 },
		{ "NOM_H", 80 },
		{ "NOM_E", 50 } 
	};
	Persona personaOrdenat[LONGITUD_VECTOR_PERSONA] = { { "NOM_A", 10 },{ "NOM_B", 20 },{ "NOM_C", 30 },{ "NOM_D", 40 },{ "NOM_E", 40 } };
	string clauStringOrdenat[LONGITUD_VECTOR_PERSONA] = { "NOM_A", "NOM_B","NOM_C","NOM_D","NOM_E" };
	string clausCerca[N_PROVES_CERCA] = { "NOM_A", "NOM_G","NOM_D","NOM_I","NOM_E", "NOM_K" };
	Persona personaCerca[N_PROVES_CERCA] = { { "NOM_A", 10 },{ "NOM_G", 70 },{ "NOM_D", 40 },{ "NOM_I", 90 },{ "NOM_E", 50 }, {"", 0} };

	cout << endl << endl;
	cout << "Comment :=>> Iniciant test de la classe MAP amb clau de tipus STRING i valor de tipus PERSONA" << endl;
	cout << "Comment :=>> ================================================================================" << endl;
	cout << "Comment :=>>  " << endl << endl;

	cout << "Comment :=>> Inicialitzant Map ....................... " << endl;
	cout << "Comment :=>> Comprovant Map Buit....................... " << endl;
	Map<string, Persona> m;

	valid = m.esBuit();
	if (!valid)
	{
		cout << "Comment :=>> ERROR" << endl;
		reduccio = 1.0;
	}
	else
		cout << "Comment :=>> CORRECTE" << endl;
	grade += (0.5 - reduccio);
	if (grade < 0)
		grade = 0.0;
	cout << endl << "Grade :=>> " << grade << endl << endl;

	cout << endl;
	cout << "Comment :=>> -----------------------------------------------" << endl;
	cout << "Comment :=>> Afegint elements al Map ....................... " << endl;
	for (int i = 0; i < N_PROVES_AFEGIR; i++)
	{
		m.afegeix(clauStringTest[i], personaTest[i]);
		cout << "Comment :=>> Element afegit: " << "<" << clauStringTest[i] << ", " << personaTest[i] << ">" << endl;
	}
	cout << "Comment :=>> --------" << endl;
	cout << "Comment :=>> Arbre amb el resultat esperat: " << endl;
	mostraFitxer("resultatEsperatAfegir.txt");
	cout << "Comment :=>> Arbre amb el resultat obtingut: " << endl;
	cout << m;

	cout << "Comment :=>> Comprovant Map resultat ....................... " << endl;
	ofstream fitxerMap;
	fitxerMap.open("resultatObtingutAfegir.txt");
	if (fitxerMap.is_open())
	{
		fitxerMap << m;
		fitxerMap.close();
	}

	if (!igualFitxers("resultatEsperatAfegir.txt", "resultatObtingutAfegir.txt"))
	{
		valid = false;
		cout << "Comment :=>> ERROR" << endl;
		reduccio = 6.0;
	}
	else
		cout << "Comment :=>> CORRECTE" << endl;
	grade += (4.0 - reduccio);
	if (grade < 0)
		grade = 0.0;
	cout << endl << "Grade :=>> " << grade << endl << endl;


	cout << endl;
	cout << "Comment :=>> -----------------------------------------------" << endl;
	cout << "Comment :=>> Comprovant acces al Map ....................... " << endl;
	for (int nProva = 0; nProva < N_PROVES_CERCA; nProva++)
	{
		cout << "Comment :=>> Clau a cercar: " << clausCerca[nProva] << endl;
		Persona p;
		p = m[clausCerca[nProva]];
		cout << "Comment :=>> --------" << endl;
		cout << "Comment :=>> Resultat esperat: " << personaCerca[nProva] << endl;
		cout << "Comment :=>> --------" << endl;
		cout << "Comment :=>> Resultat obtingut: " << p << endl;
		if ((p.getNom() != personaCerca[nProva].getNom()) && (p.getEdat() != personaCerca[nProva].getEdat()))
		{
			valid = false;
			cout << "Comment :=>> ERROR" << endl;
			reduccio = 1.0;
		}
		else
			cout << "Comment :=>> CORRECTE" << endl;

	}
	grade += (4 - reduccio);
	if (grade < 0)
		grade = 0.0;
	cout << endl << "Grade :=>> " << grade << endl << endl;




	cout << endl;
	cout << "Comment :=>> -------------------------------------------------------" << endl;
	cout << "Comment :=>> Comprovant constructor de copia ....................... " << endl;
	Map<string, Persona> mCopia(m);
	cout << "Comment :=>> --------" << endl;
	cout << "Comment :=>> Arbre amb el resultat esperat: " << endl;
	mostraFitxer("resultatEsperatAfegir.txt");
	cout << "Comment :=>> Arbre amb el resultat obtingut: " << endl;
	cout << mCopia;

	cout << "Comment :=>> Comprovant Map resultat ....................... " << endl;
	ofstream fitxerMapCopia;
	fitxerMapCopia.open("resultatObtingutCopia.txt");
	if (fitxerMapCopia.is_open())
	{
		fitxerMapCopia << mCopia;
		fitxerMapCopia.close();
	}

	if (!igualFitxers("resultatEsperatAfegir.txt", "resultatObtingutCopia.txt"))
	{
		valid = false;
		cout << "Comment :=>> ERROR" << endl;
		reduccio = 3.0;
	}
	else
		cout << "Comment :=>> CORRECTE" << endl;

	grade += (1.5 - reduccio);
	if (grade < 0)
		grade = 0.0;
	cout << endl << "Grade :=>> " << grade << endl << endl;





	if (valid)
		cout << "Comment :=>> Final del test sense errors" << endl;
	if (grade < 0)
		grade = 0;
	cout << endl << "Grade :=>> " << grade << endl;

	return 0;
}