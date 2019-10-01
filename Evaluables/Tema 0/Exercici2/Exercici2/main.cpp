#include "Hora.h"
#include <iostream>
using namespace std;

void mostraBool(bool logic)
{
	if (logic)
		cout << "TRUE";
	else
		cout << "FALSE";
}

float testHoraValida()
{
	float reduccio = 0.0;
	const int N_PROVES = 8;

	int horaTest[N_PROVES][3] =
	{
		{ 24, 1, 0},
		{ 23, 0, 0},
		{ 0, 0, 0 },
		{ 10, 30, 0 },
		{ 10, 60, 30},
		{ -1, 30, 30},
		{ 10, 30, 90},
		{ 10, 30, -1},
	};

	bool validTest[N_PROVES] = { false, true, true, true, false, false, false, false};

	cout << endl;
	cout << "Comment :=>> Iniciant test metode HORA VALIDA" << endl;
	cout << "Comment :=>> ================================" << endl;

	for (int i = 0; i < N_PROVES; i++)
	{
		Hora hora;
		hora.setHora(horaTest[i][0]);
		hora.setMinuts(horaTest[i][1]);
		hora.setSegons(horaTest[i][2]);
		cout << "Comment :=>> TEST " << i + 1 << endl;
		cout << "Comment :=>> Hora: " << hora.getHora() << ":" << hora.getMinuts() << ":" << hora.getSegons() << endl;
		cout << "Comment :=>> ---" << endl;
		cout << "Comment :=>> Valor retorn esperat: "; mostraBool(validTest[i]); cout << endl;
		cout << "Comment :=>> ---" << endl;
		bool valid = hora.horaValida();
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

float testSumaSegons()
{
	float reduccio = 0.0;
	const int N_PROVES = 8;

	Hora horaTest[N_PROVES] =
	{
		{ 10, 30, 30},
		{ 10, 30, 30 },
		{ 10, 30, 30 },
		{ 10, 30, 30 },
		{ 10, 30, 30 },
		{ 10, 30, 30 },
		{ 10, 30, 30 },
		{ 10, 30, 30 }
	};

	int nSegonsTest[N_PROVES] = { 0, 10, 30, 90, 1770, 3600, 7200, 86400 };

	Hora resultatTest[N_PROVES] =
	{
		{ 10, 30, 30 },
		{ 10, 30, 40 },
		{ 10, 31, 0 },
		{ 10, 32, 0 },
		{ 11, 0, 0 },
		{ 11, 30, 30 },
		{ 12, 30, 30 },
		{ 10, 30, 30 }
	};

	cout << endl;
	cout << "Comment :=>> Iniciant test OPERADOR SUMA + amb segons" << endl;
	cout << "Comment :=>> ========================================" << endl;

	for (int i = 0; i < N_PROVES; i++)
	{
		cout << "Comment :=>> TEST " << i + 1 << endl;
		cout << "Comment :=>> Hora: " << horaTest[i].getHora() << ":" << horaTest[i].getMinuts() << ":" << horaTest[i].getSegons() << endl;
		cout << "Comment :=>> Numero de dies: " << nSegonsTest[i] << endl;
		cout << "Comment :=>> ---" << endl;
		cout << "Comment :=>> Valor retorn esperat: " << resultatTest[i].getHora() << ":" << resultatTest[i].getMinuts() << ":" << resultatTest[i].getSegons() << endl;
		cout << "Comment :=>> ---" << endl;
		Hora resultat = horaTest[i] + nSegonsTest[i];
		cout << "Comment :=>> Valor retorn obtingut: " << resultat.getHora() << ":" << resultat.getMinuts() << ":" << resultat.getSegons() << endl;
		cout << "Comment :=>> Comparant hores amb la implementacio de l'operador == ..........." <<  endl;
		if (resultat == resultatTest[i])
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

float testSumaHores()
{
	float reduccio = 0.0;
	const int N_PROVES = 8;

	Hora horaTest[N_PROVES] =
	{
		{ 10, 30, 30 },
		{ 10, 30, 30 },
		{ 10, 30, 30 },
		{ 10, 30, 30 },
		{ 10, 30, 30 },
		{ 10, 30, 30 },
		{ 10, 30, 30 },
		{ 10, 30, 30 }
	};

	Hora horaSuma[N_PROVES] =
	{
		{ 0, 0, 0 },
		{ 0, 0, 10 },
		{ 0, 0, 30 },
		{ 0, 1, 30 },
		{ 0, 29, 30 },
		{ 1, 0, 0 },
		{ 2, 0, 0 },
		{ 23, 59, 59 }
	};

	Hora resultatTest[N_PROVES] =
	{
		{ 10, 30, 30 },
		{ 10, 30, 40 },
		{ 10, 31, 0 },
		{ 10, 32, 0 },
		{ 11, 0, 0 },
		{ 11, 30, 30 },
		{ 12, 30, 30 },
		{ 10, 30, 29 }
	};

	cout << endl;
	cout << "Comment :=>> Iniciant test OPERADOR SUMA + amb hores" << endl;
	cout << "Comment :=>> =======================================" << endl;

	for (int i = 0; i < N_PROVES; i++)
	{
		cout << "Comment :=>> TEST " << i + 1 << endl;
		cout << "Comment :=>> Hora inicial: " << horaTest[i].getHora() << ":" << horaTest[i].getMinuts() << ":" << horaTest[i].getSegons() << endl;
		cout << "Comment :=>> Hora a sumar: " << horaSuma[i].getHora() << ":" << horaSuma[i].getMinuts() << ":" << horaSuma[i].getSegons() << endl;
		cout << "Comment :=>> ---" << endl;
		cout << "Comment :=>> Valor retorn esperat: " << resultatTest[i].getHora() << ":" << resultatTest[i].getMinuts() << ":" << resultatTest[i].getSegons() << endl;
		cout << "Comment :=>> ---" << endl;
		Hora resultat = horaTest[i] + horaSuma[i];
		cout << "Comment :=>> Valor retorn obtingut: " << resultat.getHora() << ":" << resultat.getMinuts() << ":" << resultat.getSegons() << endl;
		cout << "Comment :=>> Comparant hores amb la implementacio de l'operador == ..........." << endl;
		if (resultat == resultatTest[i])
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

float testComparacioHoresMenor()
{
	float reduccio = 0.0;
	const int N_PROVES = 8;

	Hora horaTest1[N_PROVES] =
	{
		{ 10, 30, 30 },
		{ 10, 30, 30 },
		{ 10, 30, 30 },
		{ 10, 30, 30 },
		{ 10, 30, 30 },
		{ 10, 30, 30 },
		{ 10, 30, 30 },
		{ 10, 30, 30 }
	};

	Hora horaTest2[N_PROVES] =
	{
		{ 10, 30, 40 },
		{ 10, 30, 20 },
		{ 10, 20, 40 },
		{ 8, 30, 40 },
		{ 10, 40, 30 },
		{ 12, 30, 40 },
		{ 8, 30, 30 },
		{ 8, 40, 40 }
	};


	int resultatTest[N_PROVES] = { true, false, false, false, true, true, false, false};


	cout << endl;
	cout << "Comment :=>> Iniciant test OPERADOR COMPARACIO <" << endl;
	cout << "Comment :=>> ===================================" << endl;

	for (int i = 0; i < N_PROVES; i++)
	{
		cout << "Comment :=>> TEST " << i + 1 << endl;
		cout << "Comment :=>> Hora 1: " << horaTest1[i].getHora() << ":" << horaTest1[i].getMinuts() << ":" << horaTest1[i].getSegons() << endl;
		cout << "Comment :=>> Hora 2: " << horaTest2[i].getHora() << ":" << horaTest2[i].getMinuts() << ":" << horaTest2[i].getSegons() << endl;
		cout << "Comment :=>> ---" << endl;
		cout << "Comment :=>> Resultat esperat: ";  mostraBool(resultatTest[i]); cout << endl;
		cout << "Comment :=>> ---" << endl;
		bool resultat = horaTest1[i] < horaTest2[i];
		cout << "Comment :=>> Resultat obtingut: "; mostraBool(resultat); cout << endl;
		if (resultat == resultatTest[i])
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

int main()
{
	float grade = 0.0;
	float reduccio;


	cout << endl << "Grade :=>> " << grade << endl << endl;

	reduccio = testHoraValida();
	if (reduccio > 4.0)
		reduccio = 4.0;
	grade += (2.0 - reduccio);
	if (grade < 0)
		grade = 0.0;
	cout << endl << "Grade :=>> " << grade << endl << endl;

	reduccio = testSumaSegons();
	if (reduccio > 5.0)
		reduccio = 5.0;
	grade += (3.0 - reduccio);
	if (grade < 0)
		grade = 0.0;
	cout << endl << "Grade :=>> " << grade << endl << endl;

	reduccio = testSumaHores();
	if (reduccio > 5.0)
		reduccio = 5.0;
	grade += (3.0 - reduccio);
	if (grade < 0)
		grade = 0.0;
	cout << endl << "Grade :=>> " << grade << endl << endl;

	reduccio = testComparacioHoresMenor();
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