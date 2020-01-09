#include "CuaPrioritat.hpp"
#include "Tasca.h"

float testCuaPrioritat()
{
	float reduccio = 0.0;

	CuaPrioritat<Tasca> cuaTasques;

	vector<Tasca> tasquesInserir1;
	vector<string> tasquesEliminar;
	vector<Tasca> tasquesInserir2;

	tasquesInserir1 =
	{
		Tasca("T1", 5, Data(1, 1, 2018)),
		Tasca("T2", 3, Data(1, 01, 2018)),
		Tasca("T3", 2, Data(1, 1, 2018)),
		Tasca("T4", 4, Data(1, 1, 2018)),
		Tasca("T5", 1, Data(1, 1, 2018)),
		Tasca("T6", 3, Data(1, 1, 2017)),
		Tasca("T7", 2, Data(1, 9, 2018)),
		Tasca("T8", 2, Data(1, 6, 2018)),
		Tasca("T9", 3, Data(1, 6, 2018)),
		Tasca("T10", 1, Data(1, 1, 2017))
	};

	tasquesEliminar = { "T10", "T6", "T1", "T7" };

	tasquesInserir2 =
	{
		Tasca("T11", 1, Data(1, 1, 2017)),
		Tasca("T12", 3, Data(1, 1, 2017)),
		Tasca("T13", 5, Data(1, 1, 2018)),
		Tasca("T14", 2, Data(1, 9, 2018))
	};

	const int N_PROVES = 10;
	string resultat[N_PROVES] = { "T11", "T5", "T3", "T8", "T14", "T12", "T2", "T9", "T4", "T13" };

	cout << endl;
	cout << "Comment :=>> Iniciant test de la cua amb prioritat" << endl;
	cout << "Comment :=>> =====================================" << endl;
	cout << "Comment :=>>" << endl;

	cout << "Comment :=>> Inicialitzant la cua de prioritat ......." << endl;
	for (int i = 0; i < tasquesInserir1.size(); i++)
	{
		cout << "Comment :=>> Afegint tasca: " << tasquesInserir1[i].getCodi() << ", " << tasquesInserir1[i].getPrioritat() << ", " << tasquesInserir1[i].getData() << endl;
		cuaTasques.push(tasquesInserir1[i]);
	}
	for (int i = 0; i < tasquesEliminar.size(); i++)
	{
		cout << "Comment :=>> Eliminant tasca: " << tasquesEliminar[i] << endl;
		cuaTasques.remove(Tasca(tasquesEliminar[i], 0, Data()));
	}
	for (int i = 0; i < tasquesInserir2.size(); i++)
	{
		cout << "Comment :=>> Afegint tasca: " << tasquesInserir2[i].getCodi() << ", " << tasquesInserir2[i].getPrioritat() << ", " << tasquesInserir2[i].getData() << endl;
		cuaTasques.push(tasquesInserir2[i]);
	}

	cout << "Comment :=>> Recuperant elements de la cua de prioritat per ordre.... " << endl;
	for (int nProva = 0; nProva < N_PROVES; nProva++)
	{
		Tasca tascaObtinguda;

		cout << "Comment :=>>" << endl;
		cout << "Comment :=>> TEST " << nProva + 1 << endl;
		cout << "Comment :=>> -----------------------------" << endl;
		cout << "Comment :=>> Recuperant primera tasca de la cua............  " << endl;
		cout << "Comment :=>> Codi esperat de la tasca: " << resultat[nProva] << endl;
		cout << "Comment :=>> -----" << endl;
		tascaObtinguda = cuaTasques.top();
		cout << "Comment :=>> Codi obtingut de la tasca: " << tascaObtinguda.getCodi() << endl;

		if (tascaObtinguda.getCodi() == resultat[nProva])
			cout << "Comment :=>> CORRECTE" << endl;
		else
		{
			cout << "Comment :=>> ERROR" << endl;
			reduccio += 2.0;
		}
		cout << "Comment :=>> Eliminant de la cua tasca recuperada (primera de la cua)............  " << endl;
		cout << "Comment :=>> -----" << endl;
		cuaTasques.pop();
	}
	return reduccio;
}

int main()
{
	float grade = 0.0;
	float reduccio;

	cout << endl;
	cout << "Comment :=>> Iniciant test " << endl;
	cout << "Comment :=>> ==============" << endl;

	cout << endl << "Grade :=>> " << grade << endl << endl;

	reduccio = testCuaPrioritat();
	if (reduccio > 10.0)
		reduccio = 10.0;
	grade += (10.0 - reduccio);

	cout << "Grade :=>> " << grade << endl;

	if (grade < 0)
		grade = 0.0;
	cout << "Comment :=>> ------------------------------------------" << endl;
	if (grade == 10.0)
		cout << "Comment :=>> Final del test sense errors" << endl;
	cout << "Grade :=>> " << grade << endl;
	return 0;
}