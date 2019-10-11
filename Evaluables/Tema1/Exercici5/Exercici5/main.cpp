#include "SmartPointer.h"
#include "Persona.h"


int main()
{
	bool valid = true;
	float grade = 0.0;
	float reduccio = 0.0;
	cout << endl << "Grade :=>> " << grade << endl << endl;

	cout << endl << endl;
	cout << "Comment :=>> Iniciant test de la classe SMART POINTER  per elements de tipus PERSONA" << endl;
	cout << "Comment :=>> =======================================================================" << endl;
	cout << "Comment :=>>  " << endl << endl;

	
	cout << "Comment :=>> Comprovant operador d'assignacio amb un apuntador estandard ....................... " << endl;
	SmartPointer<Persona> sp1;
	Persona *p1 = new Persona("A", 10);
	sp1 = p1;
	if ((*sp1).getNom() != "A")
	{
		valid = false;
		cout << "Comment :=>> ERROR assignant una adre�a o accedint al contingut" << endl;
		reduccio = 2.0;
	}
	else 
		cout << "Comment :=>> CORRECTE" << endl;
	grade += (1.0 - reduccio);
	if (grade < 0)
		grade = 0.0;
	cout << endl << "Grade :=>> " << grade << endl << endl;

	cout << "Comment :=>> Comprovant operador d'assignacio amb un apuntador estandard ....................... " << endl;
	Persona *p2 = new Persona("B", 20);
	SmartPointer<Persona> sp2;
	sp2 = p2;
	if ((*sp2).getNom() != "B")
	{
		valid = false;
		cout << "Comment :=>> ERROR operador assignacio o accedint al contingut" << endl;
		reduccio = 2.0;
	}
	else
		cout << "Comment :=>> CORRECTE" << endl;
	grade += (1.0 - reduccio);
	if (grade < 0)
		grade = 0.0;
	cout << endl << "Grade :=>> " << grade << endl << endl;

	cout << "Comment :=>> Comprovant constructor copia ....................... " << endl;
	SmartPointer<Persona> sp3 = sp1;
	if (((*sp3).getNom() != "A") || (!sp1.isNull()))
	{
		valid = false;
		cout << "Comment :=>> ERROR constructor de copia  o accedint al contingut" << endl;
		reduccio = 3.0;
	}
	else
		cout << "Comment :=>> CORRECTE" << endl;
	grade += (2.0 - reduccio);
	if (grade < 0)
		grade = 0.0;
	cout << endl << "Grade :=>> " << grade << endl << endl;


	cout << "Comment :=>> Comprovant operador d'assignacio entre objectes de tipus Smart Pointer ....................... " << endl;
	sp1 = sp2;
	if (((*sp1).getNom() != "B") || (!sp2.isNull()))
	{
		valid = false;
		cout << "Comment :=>> ERROR operador assignacio o accedint al contingut" << endl;
		reduccio = 3.0;
	}
	else
		cout << "Comment :=>> CORRECTE" << endl;
	grade += (2.0 - reduccio);
	if (grade < 0)
		grade = 0.0;
	cout << endl << "Grade :=>> " << grade << endl << endl;

	cout << "Comment :=>> Comprovant operador d'assignacio entre objectes de tipus Smart Pointer ....................... " << endl;
	sp1 = sp3;
	if (((*sp1).getNom() != "A") || (!sp3.isNull()))
	{
		valid = false;
		cout << "Comment :=>> ERROR operador assignacio o accedint al contingut" << endl;
		reduccio = 3.0;
	}
	else
		cout << "Comment :=>> CORRECTE" << endl;
	grade += (2.0 - reduccio);
	if (grade < 0)
		grade = 0.0;
	cout << endl << "Grade :=>> " << grade << endl << endl;


	cout << "Comment :=>> Comprovant operador -> ....................... " << endl;
	SmartPointer<Persona> sp4;
	sp4 = new Persona("C", 30);
	if (sp4->getNom() != "C")
	{
		valid = false;
		cout << "Comment :=>> ERROR amb operador -> " << endl;
		reduccio = 3.0;
	}
	else
		cout << "Comment :=>> CORRECTE" << endl;
	grade += (2.0 - reduccio);
	if (grade < 0)
		grade = 0.0;
	cout << endl << "Grade :=>> " << grade << endl << endl;

	if (grade < 0)
		grade = 0;
	if (valid)
		cout << "Final del test sense errors" << endl;
	cout << "Grade :=>> " << grade << endl;


	system("pause");
	return 0;
}