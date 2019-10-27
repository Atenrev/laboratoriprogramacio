#include "Biblioteca.h"
#include <iostream>
using namespace std;

void mostraBool(bool logic)
{
	if (logic)
		cout << "TRUE";
	else
		cout << "FALSE";
}

float testRetornar(Biblioteca &b)
{
	const int MAX_PROVES = 10;
	string idUsuari[MAX_PROVES] = { "USUARI_1", "USUARI_1", "USUARI_1", "USUARI_1", "USUARI_1", "USUARI_1", "USUARI_1", "USUARI_1", "USUARI_1", "USUARI_2" };
	string codiPublicacio[MAX_PROVES] = { "CODI_4", "CODI_4", "CODI_4", "CODI_6", "CODI_2", "CODI_2", "CODI_2", "CODI_7", "CODI_8", "CODI_3"};
	Data dataRetorn[MAX_PROVES] = {
		{ 20, 1, 2018 },
		{ 22, 1, 2018 },
		{ 20, 1, 2018 },
		{ 1, 1, 2018 },
		{ 1, 2, 2018 },
		{ 1, 2, 2018 },
		{ 1, 2, 2018 },
		{ 1, 2, 2018 },
		{ 1, 2, 2018 },
		{ 1, 2, 2018 }
	};
	int codiExemplar[MAX_PROVES] = { 0, 0, 0, 0, 1, 1, 2, 1, 0, 0 };
	bool resultatEsperat[MAX_PROVES] = { true, true, false, false, true, false, false, false, false, false };
	bool dataCorrectaEsperada[MAX_PROVES] =	{ true, false, true, true, false, false, false, false, false, false	};

	float reduccio = 0.0;

	cout << endl;
	cout << "Comment :=>> Iniciant test metode RETORNAR  de biblioteca" << endl;
	cout << "Comment :=>> (Assumeix funcionament correcte de PRESTAR)" << endl;
	cout << "Comment :=>> ============================================" << endl;

	for (int i = 0; i < MAX_PROVES; i++)
	{
		cout << "Comment :=>> ------------------------------------------" << endl;
		cout << "Comment :=>> TEST RETORNAR " << i + 1 << endl;
		cout << "Comment :=>> Id Usuari: " << idUsuari[i] << endl;
		cout << "Comment :=>> Codi Publicacio: " << codiPublicacio[i] << endl;
		cout << "Comment :=>> Codi Exemplar: " << codiExemplar[i] << endl;
		cout << "Comment :=>> Data Retorn: " << dataRetorn[i] << endl;
		cout << "Comment :=>> ---" << endl;
		cout << "Comment :=>> Valor retorn esperat: "; mostraBool(resultatEsperat[i]); cout << endl;
		if (resultatEsperat[i])
		{
			cout << "Comment :=>> Valor de Data correcta esperat: "; mostraBool(dataCorrectaEsperada[i]); cout << endl;
		}
		cout << "Comment :=>> ---" << endl;

		bool dataCorrecta;
		bool valid = b.retornar(idUsuari[i], codiPublicacio[i], dataRetorn[i], dataCorrecta, codiExemplar[i]);
		cout << "Comment :=>> Valor retorn obtingut: "; mostraBool(valid); cout << endl;
		if (valid)
		{
			cout << "Comment :=>> Valor de Data correcta obtingut: "; mostraBool(dataCorrecta); cout << endl;
		}		
		if (valid == resultatEsperat[i])
		{
			if (valid)
				if (dataCorrecta == dataCorrectaEsperada[i])
					cout << "Comment :=>> CORRECTE" << endl;
				else
				{
					cout << "Comment :=>> ERROR" << endl;
					reduccio += 1.0;
				}
			else
				cout << "Comment :=>> CORRECTE" << endl;
		}
		else
		{
			cout << "Comment :=>> ERROR" << endl;
			reduccio += 1.0;
		}
	}
	return reduccio;
}



float testPrestar(Biblioteca &b)
{
	const int MAX_PROVES = 10;
	string idUsuari = "USUARI_1";
	string codiPublicacio[MAX_PROVES] = { "CODI_4", "CODI_4", "CODI_4", "CODI_3", "CODI_3", "CODI_2", "CODI_2", "CODI_5", "CODI_7", "CODI_8" };
	Data dataPrestec = { 1, 1, 2018 };
	int codiExemplar[MAX_PROVES] = {0, 0, 0, 0, 0, 1, 1, 0, 1, 0};
	bool resultatEsperat[MAX_PROVES] = { true, true, false, true, false, true, false, false, false, false };
	Data dataRetornEsperat[MAX_PROVES] = 
	{
		{ 21, 1, 2018 },
		{ 21, 1, 2018 },
		{ 21, 1, 2018 },
		{ 16, 1, 2018 },
		{ 16, 1, 2018 },
		{ 31, 1, 2018 },
		{ 31, 1, 2018 },
		{ 31, 1, 2018 },
		{ 31, 1, 2018 },
		{ 31, 1, 2018 }
	};


	Publicacio *pub;
	float reduccio = 0.0;

	cout << endl;
	cout << "Comment :=>> Iniciant test metode PRESTAR  de biblioteca" << endl;
	cout << "Comment :=>> (Assumeix funcionament correcte de llegir publicacions)" << endl;
	cout << "Comment :=>> =======================================================" << endl;

	for (int i = 0; i < MAX_PROVES; i++)
	{
		cout << "Comment :=>> ------------------------------------------" << endl;
		cout << "Comment :=>> TEST PRESTAR " << i + 1 << endl;
		cout << "Comment :=>> Id Usuari: " << idUsuari << endl;
		cout << "Comment :=>> Codi Publicacio: " << codiPublicacio[i] << endl;
		cout << "Comment :=>> Codi Exemplar: " << codiExemplar[i] << endl;
		cout << "Comment :=>> Data Prestec: " << dataPrestec << endl;
		cout << "Comment :=>> ---" << endl;
		cout << "Comment :=>> Valor retorn esperat: "; mostraBool(resultatEsperat[i]); cout << endl;
		if (resultatEsperat[i])
			cout << "Comment :=>> Data retorn esperada: " << dataRetornEsperat[i] << endl;
		cout << "Comment :=>> ---" << endl;

		Data dataRetorn;
		bool valid = b.prestar(idUsuari, codiPublicacio[i], dataPrestec, dataRetorn, codiExemplar[i]);
		cout << "Comment :=>> Valor retorn obtingut: "; mostraBool(valid); cout << endl;
		if (valid)
			cout << "Comment :=>> Data retorn obtinguda: " << dataRetorn << endl;
		if (valid == resultatEsperat[i])
		{
			if (valid)
				if (dataRetorn == dataRetornEsperat[i])
					cout << "Comment :=>> CORRECTE" << endl;
				else
				{
					cout << "Comment :=>> ERROR" << endl;
					reduccio += 1.0;
				}
			else
				cout << "Comment :=>> CORRECTE" << endl;
		}
		else
		{
			cout << "Comment :=>> ERROR" << endl;
			reduccio += 1.0;
		}
	}
	return reduccio;
}


int main()
{
	float grade = 0.0;
	float reduccio;


	Biblioteca b;

	cout << endl;
	cout << "Comment :=>> Iniciant test " << endl;
	cout << "Comment :=>> ==============" << endl;

	cout << endl << "Grade :=>> " << grade << endl << endl;

	cout << endl;
	cout << "Comment :=>> Llegint fitxer 'biblioteca.txt' per inicialitzar dades de les publicacions..........." << endl;
	cout << "Comment :=>> =====================================================================================" << endl;
	b.llegirPublicacions("biblioteca.txt");


	reduccio = testPrestar(b);
	if (reduccio > 6.0)
		reduccio = 6.0;
	grade += (5.0 - reduccio);

	cout << "Grade :=>> " << grade << endl;

	reduccio = testRetornar(b);
	if (reduccio > 6.0)
		reduccio = 6.0;
	grade += (5.0 - reduccio);


	if (grade < 0)
		grade = 0.0;
	cout << "Comment :=>> ------------------------------------------" << endl;
	if (grade == 10.0)
		cout << "Comment :=>> Final del test sense errors" << endl;
	cout << "Grade :=>> " << grade << endl;
	return 0;

}