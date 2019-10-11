#include "Map.h"
#include "Persona.h"
#include <iostream>
#include <string>
#include <time.h>
using namespace std;

template <class T1, class T2>
void escriuValors(T1 valors1[], T2 valors2[], int nValors)
{
	cout << "[";
	for (int i = 0; i < nValors - 1; i++)
	{
		cout << "<" << valors1[i] << "," << valors2[i] << ">" << ", ";
	}
	if (nValors > 0)
		cout << "<" << valors1[nValors - 1] << "," << valors2[nValors - 1] << ">";
	cout << "]";
}

template <class T1, class T2>
void escriuMap(const Map<T1, T2>& m)
{
	cout << "[";
	for (int i = 0; i < m.longitud() - 1; i++)
	{
		T1 c = m[i];
		T2 v = m[m[i]];
		cout << "<" << m[i] << "," << m[m[i]] << ">" << ", ";
	}
	if (m.longitud() > 0)
		cout << "<" << m[m.longitud() - 1] << "," << m[m[m.longitud() - 1]] << ">";
	cout << "]";
}

template <class T1, class T2>
bool comparaMap(const Map<T1, T2>& m, T1 valors1[], T2 valors2[])
{
	bool iguals = true;
	int i = 0;
	while (iguals && (i < m.longitud()))
	{
		if ((m[i] != valors1[i]) || !(m[m[i]] == valors2[i]))
			iguals = false;
		else
			i++;
	}
	return iguals;
}

int main()
{
	bool valid = true;
	float reduccio = 0.0;
	float grade = 0.0;
	cout << endl << "Grade :=>> " << grade << endl << endl;

	const int N_PROVES = 6;
	const int N_PROVES_CERCA = 5;
	const int N_PROVES_AFEGIR = 6;
	const int LONGITUD_VECTOR_PERSONA = 5;

	Persona personaTest[N_PROVES_AFEGIR] = { { "NOM_B", 20 }, { "NOM_A", 10 },{ "NOM_D", 40 },{ "NOM_C", 30 },{ "NOM_E", 20 },{ "NOM_E", 40 } };
	Persona personaOrdenat[LONGITUD_VECTOR_PERSONA] = { { "NOM_A", 10 },{ "NOM_B", 20 },{ "NOM_C", 30 },{ "NOM_D", 40 },{ "NOM_E", 40 } };
	string clauStringTest[N_PROVES_AFEGIR] = { "NOM_B", "NOM_A", "NOM_D", "NOM_C","NOM_E", "NOM_E" };
	string clauStringOrdenat[LONGITUD_VECTOR_PERSONA] = { "NOM_A", "NOM_B","NOM_C","NOM_D","NOM_E" };

	cout << endl << endl;
	cout << "Comment :=>> Iniciant test de la classe MAP amb clau de tipus STRING i valor de tipus PERSONA" << endl;
	cout << "Comment :=>> ================================================================================" << endl;
	cout << "Comment :=>>  " << endl << endl;

	cout << "Comment :=>> Inicialitzant Map ....................... " << endl;
	cout << "Comment :=>> Comprovant Map Buit....................... " << endl;
	Map<string, Persona> m;

	valid = ((m.esBuit()) && (m.longitud() == 0));
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
	cout << "Comment :=>> Resultat esperat: " << endl;
	cout << "Comment :=>> "; escriuValors(clauStringOrdenat, personaOrdenat, LONGITUD_VECTOR_PERSONA); cout << endl;
	cout << "Comment :=>> Resultat obtingut: " << endl;
	cout << "Comment :=>> "; escriuMap(m); cout << endl;

	cout << "Comment :=>> Comprovant Map resultat (suposa funcionament correcte operadors []) ....................... " << endl;

	if (!comparaMap(m, clauStringOrdenat, personaOrdenat))
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
	cout << "Comment :=>> -----------------------------------------------------------------------" << endl;
	cout << "Comment :=>> Comprovant acces al Map amb una clau inexistent ....................... " << endl;
	cout << "Comment :=>> --------" << endl;
	Persona p;
	p = m["A"];
	cout << "Comment :=>> Resultat esperat: " << Persona() << endl;
	cout << "Comment :=>> Resultat obtingut: " << p << endl;
	if ((p.getNom() != "") && (p.getEdat() != 0))
	{
		valid = false;
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
	cout << "Comment :=>> -------------------------------------------------------------------" << endl;
	cout << "Comment :=>> Comprovant operador d'assignacio entre maps ....................... " << endl;
	Map<string, Persona> m2 = m;
	cout << "Comment :=>> --------" << endl;
	cout << "Comment :=>> Resultat esperat: " << endl;
	cout << "Comment :=>> "; escriuValors(clauStringOrdenat, personaOrdenat, LONGITUD_VECTOR_PERSONA); cout << endl;
	cout << "Comment :=>> Resultat obtingut: " << endl;
	cout << "Comment :=>> "; escriuMap(m2); cout << endl;

	cout << "Comment :=>> Comprovant Map resultat (suposa funcionament correcte operadors []) ....................... " << endl;

	if (!comparaMap(m2, clauStringOrdenat, personaOrdenat))
	{
		valid = false;
		cout << "Comment :=>> ERROR" << endl;
		reduccio = 3.0;
	}
	else
		cout << "Comment :=>> CORRECTE" << endl;
	grade += (2.0 - reduccio);
	if (grade < 0)
		grade = 0.0;
	cout << endl << "Grade :=>> " << grade << endl << endl;

	cout << endl;
	cout << "Comment :=>> -------------------------------------------------------" << endl;
	cout << "Comment :=>> Comprovant constructor de copia ....................... " << endl;
	Map<string, Persona> m3(m);
	cout << "Comment :=>> --------" << endl;
	cout << "Comment :=>> Resultat esperat: " << endl;
	cout << "Comment :=>> "; escriuValors(clauStringOrdenat, personaOrdenat, LONGITUD_VECTOR_PERSONA); cout << endl;
	cout << "Comment :=>> Resultat obtingut: " << endl;
	cout << "Comment :=>> "; escriuMap(m3); cout << endl;

	cout << "Comment :=>> Comprovant Map resultat (suposa funcionament correcte operadors []) ....................... " << endl;

	if (!comparaMap(m3, clauStringOrdenat, personaOrdenat))
	{
		valid = false;
		cout << "Comment :=>> ERROR" << endl;
		reduccio = 3.0;
	}
	else
		cout << "Comment :=>> CORRECTE" << endl;
	grade += (2.0 - reduccio);
	if (grade < 0)
		grade = 0.0;
	cout << endl << "Grade :=>> " << grade << endl << endl;


	const float FACTOR_EFICIENCIA = 0.3;

	cout << endl;
	cout << "Comment :=>> --------------------------------------------------------------------------------" << endl;
	cout << "Comment :=>> Comprovant eficiencia de la cerca binaria a l'operador[] ....................... " << endl;
	float tempsAcumulatCercaBinaria = 0;
	float tempsAcumulatNoCercaBinaria = 0;
	const int MAX_VECTOR = 1000;
	Map<string, Persona> mapTest;
	
	string clauTest = to_string(2000000);
	for (int i = 0; i < MAX_VECTOR; i++)
	{
		mapTest.afegeix(to_string(i), Persona());
	}

	clock_t timeCercaBinaria;
	timeCercaBinaria = clock();
	for (int j = 0; j < 10000; j++)
	{
		Persona valor = mapTest[clauTest];
	}
	timeCercaBinaria = clock() - timeCercaBinaria;
	tempsAcumulatCercaBinaria += (float)timeCercaBinaria / CLOCKS_PER_SEC;

	clock_t timeNoCercaBinaria;
	timeNoCercaBinaria = clock();
	for (int j = 0; j < 10000; j++)
	{
		bool trobat = false;
		int i = 0;
		while (!trobat && (i < MAX_VECTOR))
		{
			if (mapTest[i] >= clauTest)
				trobat = true;
			else
				i++;

		}
	}
	timeNoCercaBinaria = clock() - timeNoCercaBinaria;
	tempsAcumulatNoCercaBinaria += (float)timeNoCercaBinaria / CLOCKS_PER_SEC;

	cout << "Comment :=>> Temps per realitzar operador[] amb cerca binaria: " << tempsAcumulatCercaBinaria << endl;
	cout << "Comment :=>> Temps per realitzar operador[] sense cerca binaria: " << tempsAcumulatNoCercaBinaria << endl;
	if (tempsAcumulatCercaBinaria < (FACTOR_EFICIENCIA * tempsAcumulatNoCercaBinaria))
		cout << "Comment :=>> CORRECTE" << endl;
	else
	{
		cout << "Comment :=>> ERROR" << endl;
		cout << "Comment :=>> S'esperava una major reduccio del temps a l'aplicar la cerca binaria" << endl;
		reduccio = 1.0;
		cout << "Comment :=>> -----------------------------------------------" << endl;
	}
	grade += (1.0 - reduccio);
	if (grade < 0)
		grade = 0.0;
	cout << endl << "Grade :=>> " << grade << endl << endl;




	if (valid)
		cout << "Comment :=>> Final del test sense errors" << endl;
	if (grade < 0)
		grade = 0;
	cout << endl << "Grade :=>> " << grade << endl;

	system("pause");
	return 0;
}