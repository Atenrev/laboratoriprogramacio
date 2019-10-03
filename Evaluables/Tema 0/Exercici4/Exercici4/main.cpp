#include <iostream>
#include "Exercici.h"
using namespace std;


void mostraBool(bool logic)
{
	if (logic)
		cout << "TRUE";
	else
		cout << "FALSE";
}


float testAfegeixTramesa(Exercici* e)
{
	float reduccio = 0.0;
	const int N_PROVES = 8;

	string dadesTest[N_PROVES][3] =
	{
		{ "1111111", "01/01/19",  "fitxer1"},
		{ "1111111", "02/01/19",  "fitxer2" },
		{ "1111111", "03/01/19",  "fitxer3" },
		{ "1111111", "04/01/19",  "fitxer4" },
		{ "2222222", "01/01/19",  "fitxer5" },
		{ "2222222", "01/02/19",  "fitxer6" },
		{ "3333333", "01/02/19",  "fitxer7" },
		{ "5555555", "01/02/19",  "fitxer6" },
	};

	bool validTest[N_PROVES] = { true, true, true, true, true, true, true, false };

	cout << endl;
	cout << "Comment :=>> Iniciant test metode AFEGEIX TRAMESA" << endl;
	cout << "Comment :=>> ====================================" << endl;

	for (int i = 0; i < N_PROVES; i++)
	{
		cout << "Comment :=>> TEST " << i + 1 << endl;
		cout << "Comment :=>> Niu: " << dadesTest[i][0] << endl;
		cout << "Comment :=>> Data: " << dadesTest[i][1] << endl;
		cout << "Comment :=>> Fitxer: " << dadesTest[i][2] << endl;
		cout << "Comment :=>> ---" << endl;
		cout << "Comment :=>> Valor retorn esperat: "; mostraBool(validTest[i]); cout << endl;
		cout << "Comment :=>> ---" << endl;
		bool valid = e->afegeixTramesa(dadesTest[i][0], dadesTest[i][2], dadesTest[i][1]);
		cout << "Comment :=>> Valor retorn obtingut: "; mostraBool(valid); cout << endl;
		if (valid == validTest[i])
			cout << "Comment :=>> CORRECTE" << endl;
		else
		{
			cout << "Comment :=>> ERROR" << endl;
			reduccio += 1.0;
		}
		cout << "Comment :=>> ------------------------------------------" << endl;
	}
	return reduccio;
}


float testEliminaTramesa(Exercici* e)
{
	float reduccio = 0.0;
	const int N_PROVES = 8;

	string dadesTest[N_PROVES][2] =
	{
		{ "1111111", "02/01/19" },
		{ "1111111", "04/01/19" },
		{ "2222222", "01/01/19" },
		{ "3333333", "01/02/19" },
		{ "5555555", "01/02/19" },
		{ "1111111", "05/02/19" },
	};

	bool validTest[N_PROVES] = { true, true, true, true, false, false };

	cout << endl;
	cout << "Comment :=>> Iniciant test metode ELIMINA TRAMESA" << endl;
	cout << "Comment :=>> ====================================" << endl;

	for (int i = 0; i < N_PROVES; i++)
	{
		cout << "Comment :=>> TEST " << i + 1 << endl;
		cout << "Comment :=>> Niu: " << dadesTest[i][0] << endl;
		cout << "Comment :=>> Data: " << dadesTest[i][1] << endl;
		cout << "Comment :=>> ---" << endl;
		cout << "Comment :=>> Valor retorn esperat: "; mostraBool(validTest[i]); cout << endl;
		cout << "Comment :=>> ---" << endl;
		bool valid = e->eliminaTramesa(dadesTest[i][0], dadesTest[i][1]);
		cout << "Comment :=>> Valor retorn obtingut: "; mostraBool(valid); cout << endl;
		if (valid == validTest[i])
			cout << "Comment :=>> CORRECTE" << endl;
		else
		{
			cout << "Comment :=>> ERROR" << endl;
			reduccio += 1.0;
		}
		cout << "Comment :=>> ------------------------------------------" << endl;
	}
	return reduccio;
}


float testConsultaTramesa(Exercici* e)
{
	float reduccio = 0.0;
	const int N_PROVES = 9;

	string dadesTest[N_PROVES][2] =
	{
		{ "1111111", "02/01/19" },
		{ "1111111", "04/01/19" },
		{ "2222222", "01/01/19" },
		{ "3333333", "01/02/19" },
		{ "5555555", "01/02/19" },
		{ "1111111", "05/02/19" },
		{ "1111111", "01/01/19" },
		{ "1111111", "03/01/19" },
		{ "2222222", "01/02/19" },
	};

	bool validTest[N_PROVES] = { false, false, false, false, false, false, true, true, true };
	string fitxerTest[N_PROVES] = { "", "", "", "", "", "", "fitxer1", "fitxer3", "fitxer6" };


	cout << "Comment :=>> " << endl;
	cout << "Comment :=>> Iniciant test metode CONSULTA TRAMESA" << endl;
	cout << "Comment :=>> =====================================" << endl;

	for (int i = 0; i < N_PROVES; i++)
	{
		cout << "Comment :=>> TEST " << i + 1 << endl;
		cout << "Comment :=>> Niu: " << dadesTest[i][0] << endl;
		cout << "Comment :=>> Data: " << dadesTest[i][1] << endl;
		cout << "Comment :=>> ---" << endl;
		cout << "Comment :=>> Valor retorn esperat: "; mostraBool(validTest[i]); cout << endl;
		if (validTest[i])
			cout << "Comment :=>> Fitxer esperat: " << fitxerTest[i] << endl;
		cout << "Comment :=>> ---" << endl;
		string fitxer;
		bool valid = e->consultaTramesa(dadesTest[i][0], dadesTest[i][1], fitxer);
		cout << "Comment :=>> Valor retorn obtingut: "; mostraBool(valid); cout << endl;
		if (valid)
			cout << "Comment :=>> Fitxer obtingut: " << fitxer << endl;
		if (valid == validTest[i])
			if (valid)
				if (fitxer == fitxerTest[i])
					cout << "Comment :=>> CORRECTE" << endl;
				else
				{
					cout << "Comment :=>> ERROR" << endl;
					reduccio += 1.0;
				}
			else
				cout << "Comment :=>> CORRECTE" << endl;
		else
		{
			cout << "Comment :=>> ERROR" << endl;
			reduccio += 1.0;
		}
		cout << "Comment :=>> ------------------------------------------" << endl;
	}
	return reduccio;
}


float testConstructorCopia(Exercici* e)
{
	float reduccio = 0.0;

	cout << "Comment :=>> " << endl;
	cout << "Comment :=>> Iniciant test CONSTRUCTOR COPIA" << endl;
	cout << "Comment :=>> ===============================" << endl;

	cout << "Comment :=>> " << endl;
	cout << "Comment :=>> Creant la copia....." << endl;
	cout << "Comment :=>> --------------------" << endl;
	Exercici* eCopia = new Exercici(*e);
	e->afegeixTramesa("1111111", "fitxer", "02/01/19");
	e->afegeixTramesa("1111111", "fitxer", "04/01/19");
	e->afegeixTramesa("2222222", "fitxer", "01/01/19");
	e->afegeixTramesa("3333333", "fitxer", "01/02/19");
	e->eliminaTramesa("1111111", "01/01/19");
	e->eliminaTramesa("1111111", "03/01/19");
	e->eliminaTramesa("2222222", "01/02/19");


	cout << "Comment :=>> " << endl;
	cout << "Comment :=>> Comprovant la copia repetint el test de CONSULTA TRAMESA aplicat a la copia....." << endl;
	cout << "Comment :=>> --------------------------------------------------------------------------------" << endl;

	reduccio = testConsultaTramesa(eCopia);

	e->eliminaTramesa("1111111", "02/01/19");
	e->eliminaTramesa("1111111", "04/01/19");
	e->eliminaTramesa("2222222", "01/01/19");
	e->eliminaTramesa("3333333", "01/02/19");
	e->afegeixTramesa("1111111", "fitxer1", "01/01/19");
	e->afegeixTramesa("1111111", "fitxer3", "03/01/19");
	e->afegeixTramesa("2222222", "fitxer6", "01/02/19");
	return reduccio;
}


float testOperadorAssignacio(Exercici* e)
{
	float reduccio = 0.0;

	cout << "Comment :=>> " << endl;
	cout << "Comment :=>> Iniciant test OPERADOR ASSIGNACIO" << endl;
	cout << "Comment :=>> =================================" << endl;

	cout << "Comment :=>> " << endl;
	cout << "Comment :=>> Fent l'assignacio....." << endl;
	cout << "Comment :=>> ----------------------" << endl;
	Exercici eCopia;
	eCopia = *e;
	e->afegeixTramesa("1111111", "fitxer", "02/01/19");
	e->afegeixTramesa("1111111", "fitxer", "04/01/19");
	e->afegeixTramesa("2222222", "fitxer", "01/01/19");
	e->afegeixTramesa("3333333", "fitxer", "01/02/19");
	e->eliminaTramesa("1111111", "01/01/19");
	e->eliminaTramesa("1111111", "03/01/19");
	e->eliminaTramesa("2222222", "01/02/19");
	delete e;

	cout << "Comment :=>> " << endl;
	cout << "Comment :=>> Comprovant la copia repetint el test de CONSULTA TRAMESA aplicat a la copia....." << endl;
	cout << "Comment :=>> --------------------------------------------------------------------------------" << endl;

	reduccio = testConsultaTramesa(&eCopia);

	return reduccio;
}


int main()
{
	float reduccio = 0;
	float grade = 0.0;

	Exercici* e = new Exercici;
	cout << endl << "Grade :=>> " << grade << endl << endl;
	cout << "Comment : = >> " << endl;
	cout << "Comment :=>> Inicialitzant estudiants de l'exercici a partir del fitxer 'estudiants.txt'" << endl;
	cout << "Comment :=>> ===========================================================================" << endl;
	cout << "Comment :=>> " << endl;
	e->inicialitzaEstudiants("estudiants.txt");

	reduccio = testAfegeixTramesa(e);
	if (reduccio > 4.0)
		reduccio = 4.0;
	grade += (2.0 - reduccio);
	if (grade < 0)
		grade = 0.0;
	cout << endl << "Grade :=>> " << grade << endl << endl;

	reduccio = testEliminaTramesa(e);
	if (reduccio > 4.0)
		reduccio = 4.0;
	grade += (2.0 - reduccio);
	if (grade < 0)
		grade = 0.0;
	cout << endl << "Grade :=>> " << grade << endl << endl;

	reduccio = testConsultaTramesa(e);
	if (reduccio > 4.0)
		reduccio = 4.0;
	grade += (2.0 - reduccio);
	if (grade < 0)
		grade = 0.0;
	cout << endl << "Grade :=>> " << grade << endl << endl;

	reduccio = testConstructorCopia(e);
	if (reduccio > 4.0)
		reduccio = 4.0;
	grade += (2.0 - reduccio);
	if (grade < 0)
		grade = 0.0;
	cout << endl << "Grade :=>> " << grade << endl << endl;

	reduccio = testOperadorAssignacio(e);
	if (reduccio > 4.0)
		reduccio = 4.0;
	grade += (2.0 - reduccio);
	if (grade < 0)
		grade = 0.0;
	cout << endl << "Grade :=>> " << grade << endl << endl;

	if (grade < 0)
		grade = 0.0;
	cout << "Comment :=>> ------------------------------------------" << endl;
	if (grade == 10.0)
		cout << "Comment :=>> Final del test sense errors" << endl;
	cout << "Grade :=>> " << grade << endl;

	system("pause");

	return 0;
}