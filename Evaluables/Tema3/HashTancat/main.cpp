#include <iostream>
using namespace std;
#include "Hash.h"

void imprimirvect(vector<pair<string, string>>&  vSol)
{
	for (int i = 0; i < vSol.size(); i++)
	{
		if (vSol[i].first != "")
		{
			cout << "POS: " << i << "  CLAU: " << vSol[i].first << "  VALOR: " << vSol[i].second << endl; 
		}
	}
}
bool Iguals(Hash& h, vector<pair<string, string>>&  vSol)
{
	int i = 0;
	bool diferents = false;
	while ((i < vSol.size()) && !diferents)
	{
		if (vSol[i] != h[i])
		{
			diferents = true;
		}
		i++;
	}
	return !diferents;
}

int main()
{
	try
	{
		bool valid = true;
		float reduccio = 0.0;
		float grade = 0.0;
		cout << endl << "Grade :=>> " << grade << endl << endl;

		vector<pair<string, string>> vSol,vSol2,vSol3;
		vSol.resize(20,pair<string,string>("",""));
		vSol2.resize(20, pair<string, string>("", ""));
		vSol3.resize(20, pair<string, string>("", ""));
		vSol = { {"Ornitorrinc","Animal."},{"",""},{"Hola" ,"Es una salutacio." },{ "","" },{ "","" },{ "Adeu","Es un comiat." },{ "Dia", "Es un periode de 24 hores." },
		{ "","" },{ "","" },{ "Any", "Es un periode de 12 mesos." },{ "","" },{ "","" },{ "","" },{ "","" },{ "","" },{ "","" },{ "","" },{ "","" },{ "","" },{ "Mes", "Es un periode de entre 28 i 31 dies." } };
		vSol2 = { { "Ornitorrinc","Animal." },{ "","" },{ "Hola" ,"Es una salutacio." },{ "","" },{ "","" },{ "Adeu","Es un comiat." },{ "Dia", "Es un periode de 24 hores." },
		{ "","" },{ "","" },{ "Any", "Es un periode de 12 mesos." },{ "","" },{ "","" },{ "","" },{ "","" },{ "","" },{ "","" },{ "","" },{ "","" },{ "","" },{ "", "" } };
		vSol3 = { { "Ornitorrinc","Animal." },{ "","" },{ "Hola" ,"Es una salutacio." },{ "","" },{ "","" },{ "Adeu","Es un comiat." },{ "Dia", "Es un periode de 24 hores." },
		{ "","" },{ "","" },{ "Any", "Es un periode de 12 mesos." },{ "","" },{ "","" },{ "","" },{ "","" },{ "","" },{ "","" },{ "","" },{ "","" },{ "","" },{ "Estel", "Cos celeste amb llum propia" } };

		cout << endl << endl;
		cout << "Comment :=>> Iniciant test de la classe HASH       " << endl;
		cout << "Comment :=>> ======================================" << endl;
		cout << "Comment :=>>  " << endl << endl;

		Hash h;
		const int MAXELEMENTS = 6;
		pair<string, string> vEntrada[MAXELEMENTS] = { pair<string,string>("Hola", "Es una salutacio."),
		pair<string,string>("Adeu","Es un comiat."),
		pair<string,string>("Dia", "Es un periode de 24 hores."),
		pair<string,string>("Mes", "Es un periode de entre 28 i 31 dies."),
		pair<string,string>("Any", "Es un periode de 12 mesos."),
		pair<string,string>("Ornitorrinc", "Animal."),
		};

		cout << "Comment :=>> ==========================================" << endl;
		cout << "Comment :=>> Inserint Elements ....................... " << endl;
		for (int i = 0; i < MAXELEMENTS; i++)
		{
			h.insert(vEntrada[i].first, vEntrada[i].second);			
		}

		if (Iguals(h, vSol))
		{
			cout << "Comment :=>> OK Inserint elements ....................... " << endl;
			cout << "Comment :=>> Escrivint DICCIONARI ....................... " << endl;
			cout << h;			
		}
		else
		{
			cout << "Comment :=>> ERROR Inserint elements ....................... " << endl;
			cout << "Comment :=>> DICCIONARI OBTINGUT     ....................... " << endl;
			cout << h;
			cout << "Comment :=>> DICCIONARI ESPERAT     ....................... " << endl;
			imprimirvect( vSol);
			grade = grade - 2;
		}

		cout << "Comment :=>> ==========================================" << endl;
		cout << "Comment :=>> Buscant elements no existents amb []..... " << endl;

		cout << "Comment :=>> Definicio de caleidoscopi es: " << h["caleidoscopi"] <<endl;
		cout << "Comment :=>> Definicio d'eina es: " << h["eina"] <<endl;

		if (Iguals(h, vSol))
		{
			cout << "Comment :=>> OK Cercant elements no existents amb [] ....................... " << endl;
			cout << "Comment :=>> Escrivint DICCIONARI ....................... " << endl;
			cout << h;
			grade = grade + 2;
		}
		else
		{
			cout << "Comment :=>> ERROR Cercant elements no existents amb [] ....................... " << endl;
			cout << "Comment :=>> DICCIONARI OBTINGUT     ....................... " << endl;
			cout << h;
			cout << "Comment :=>> DICCIONARI ESPERAT     ....................... " << endl;
			imprimirvect(vSol);			
		}
		
		cout << "Comment :=>> ================================" << endl;
		cout << "Comment :=>> Esborrant element existent..... " << endl;
		cout << "Comment :=>> ESBORRO Mes ===" << endl;
		bool esborrat=	h.esborra("Mes");

		if (esborrat)
		{
			cout << "Comment :=>> Mes ha tornat true a Esborra OK" <<endl;
			if (Iguals(h, vSol2))
			{
				cout << "Comment :=>> OK Esborrant elements ....................... " << endl;
				cout << "Comment :=>> Escrivint DICCIONARI ....................... " << endl;
				cout << h;
				grade = grade + 2;
			}
			else
			{
				cout << "Comment :=>> ERROR Esborrant elements ....................... " << endl;
				cout << "Comment :=>> DICCIONARI OBTINGUT     ....................... " << endl;
				cout << h;
				cout << "Comment :=>> DICCIONARI ESPERAT     ....................... " << endl;
				imprimirvect(vSol2);
			}
		}
		else
			cout << "Comment :=>> Mes ha tornat false a Esborra ERROR" << endl;
		
		
		cout << "Comment :=>> ===================================" << endl;
		cout << "Comment :=>> Esborrant element no existent..... " << endl;

		cout << "Comment :=>> ESBORRO taula===" << endl;
		esborrat = h.esborra("taula");
		if (esborrat)
		{
			cout << "Comment :=>> Esborra taula ha tornat true ERROR. taula no existeix" << endl;
		}
		else
		{
			cout << "Comment :=>> Esborra taula ha tornat false OK. taula no existeix" << endl;
			if (Iguals(h, vSol2))
			{
				cout << "Comment :=>> OK Esborrant element no existent............ " << endl;
				cout << "Comment :=>> Escrivint DICCIONARI ....................... " << endl;
				cout << h;
				grade = grade + 2;
			}
			else
			{
				cout << "Comment :=>> ERROR Esborrant element no existent............ " << endl;
				cout << "Comment :=>> DICCIONARI OBTINGUT     ....................... " << endl;
				cout << h;
				cout << "Comment :=>> DICCIONARI ESPERAT     ....................... " << endl;
				imprimirvect(vSol2);
			}
		}
		
		cout << "Comment :=>> ===============================" << endl;
		cout << "Comment :=>> Inserint element existent..... " << endl;
		h.insert("Ornitorrinc", "Animal Mamifer.");
		if (Iguals(h, vSol2))
		{
			cout << "Comment :=>> OK Inserint element existent............ " << endl;
			cout << "Comment :=>> Escrivint DICCIONARI.................... " << endl;
			cout << h;
			grade = grade + 2;
		}
		else
		{
			cout << "Comment :=>> ERROR Inserint element existent............ " << endl;
			cout << "Comment :=>> DICCIONARI OBTINGUT    .................... " << endl;
			cout << h;
			cout << "Comment :=>> DICCIONARI ESPERAT     ....................... " << endl;
			imprimirvect(vSol2);
		}

		cout << "Comment :=>> ==================================" << endl;
		cout << "Comment :=>> Inserint element no existent..... " << endl;
		cout << "Comment :=>> Inserint Estel" << endl;
		h.insert("Estel","Cos celeste amb llum propia");

		if (Iguals(h, vSol3))
		{
			cout << "Comment :=>> OK Inserint element no existent............ " << endl;
			cout << "Comment :=>> Escrivint DICCIONARI....................... " << endl;
			cout << h;
			grade = grade + 2;
		}
		else
		{
			cout << "Comment :=>> ERROR Inserint element no existent............ " << endl;
			cout << "Comment :=>> DICCIONARI OBTINGUT    ....................... " << endl;
			cout << h;
			cout << "Comment :=>> DICCIONARI ESPERAT     ....................... " << endl;
			imprimirvect(vSol3);
		}



		if (valid)
			cout << "Comment :=>> Final del test sense errors" << endl;
		if (grade < 0)
			grade = 0;
		cout << endl << "Grade :=>> " << grade << endl;

		return 0;
	}
	catch (const char* msg)
	{
		cout << msg;
	}
	catch (std::out_of_range)
	{
		cout << "Intentes accedir a una posició fora del vector";
	}	
}