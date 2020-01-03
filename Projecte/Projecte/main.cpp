#include "Graph.h"

bool IgualFitxers(string nomF1, string nomF2, string nomFRes)
{
	ifstream f1,f2;
	f1.open(nomF1);
	f2.open(nomF2);
	bool iguals = true;

	if (f1.is_open() && f2.is_open()) 
	{
		ofstream fitxCompara(nomFRes, ios::out);
		int cont = 0, linia = 0;
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
			{ 
				++cont;
				fitxCompara << flush << "Error num " << cont << " a linia " << linia << endl << flush;
				iguals = false;				
			}
		}
		if (!f1.eof() && f2.eof()) 
		{
			fitxCompara << "Fitxer " << nomF2 << " es mes curt que " << nomF1 << endl;
		}
		if (!f2.eof() && f1.eof()) 
		{
			fitxCompara << "Fitxer " << nomF1 << " es mes curt que " << nomF2 << endl;
		}
		fitxCompara.close();		
	}
	else
	{
		throw "Error al fitxer de sortida al comparar.";
	}
	return iguals;
}

bool comparaVectInt(vector<int>& v, string nomF,string nomFOK,string nomFComp)
{
	ofstream fXarxa;

	fXarxa.open(nomF);
	if (fXarxa.is_open())
	{
		for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
		{
			fXarxa << (*it) << endl;
		}
		fXarxa.close();		
	}
	return IgualFitxers(nomF, nomFOK, nomFComp);	
}

bool comparaVectDoub(vector<double>& v, string nomF, string nomFOK, string nomFComp)
{
	ofstream fXarxa;

	fXarxa.open(nomF);
	if (fXarxa.is_open())
	{
		for (vector<double>::iterator it = v.begin(); it != v.end(); it++)
		{
			fXarxa << (*it) << endl;
		}
		fXarxa.close();
	}
	return IgualFitxers(nomF, nomFOK, nomFComp);
}
bool comparaVectPair(vector<pair<int, int>>& v, string nomF, string nomFOK, string nomFComp)
{
	ofstream fXarxa;

	fXarxa.open(nomF);
	if (fXarxa.is_open())
	{
		for (vector<pair<int, int>>::iterator it = v.begin(); it != v.end(); it++)
		{
			fXarxa << (*it).first <<" " << (*it).second << endl;
		}
		fXarxa.close();
	}
	return IgualFitxers(nomF, nomFOK, nomFComp);
}

bool comparaVectMap(vector<map<pair<int, int>, double>>& v, string nomF, string nomFOK, string nomFComp)
{
	ofstream fXarxa;

	fXarxa.open(nomF);
	if (fXarxa.is_open())
	{
		for (vector<map<pair<int, int>, double>>::iterator it = v.begin(); it != v.end(); it++)
		{
			for (map<pair<int, int>, double>::iterator itMap = (*it).begin(); itMap != (*it).end(); itMap++)
			{
				fXarxa << (*itMap).first.first <<" " <<(*itMap).first.second <<" " << (*itMap).second << endl;
			}			
		}
		fXarxa.close();
	}
	return IgualFitxers(nomF, nomFOK, nomFComp);	
}

bool comparaHeap(Heap& hTotal, string nomF, string nomFOK, string nomFComp)
{
	ofstream fXarxa;

	fXarxa.open(nomF);
	if (fXarxa.is_open())
	{
		fXarxa << hTotal;
		fXarxa.close();
	}
	return IgualFitxers(nomF, nomFOK, nomFComp);	
}

int main()
{

	try
	{
		double grade = 0.0;
		bool valid = true;
		int OKM2[3] = { 38,156,811480 };
		cout << "Comment :=>> =============================================================" << endl;
		cout << "Comment :=>> TEST SOBRE XARXACOM.........................................." << endl;
		cout << "Comment :=>> =============================================================" << endl;
		string nomFitxer = "XarxaCom.txt";

		cout << "Comment :=>> =============================================================" << endl;
		cout << "Comment :=>> LLEGINT I CREANT MATRIU I COMUNITAT XARXACOM................." << endl;
		MatriuSparse mXarxaCom(nomFitxer);
		Comunitat cXarxaCom(&mXarxaCom);

		cout << "Comment :=>> ======================================" << endl;
		cout << "Comment :=>> CALCULANT M2 XARXACOM................." << endl;
		cXarxaCom.calculaM2();
		int m2XarxaCom = cXarxaCom.getM2();
		cout << "Comment :=>> M2 CALCULAT: " << m2XarxaCom <<endl;
		if (m2XarxaCom == OKM2[0])
		{
			cout << "Comment :=>> M2 XARXACOM CALCULAT OK .............." << endl;
			grade+=0.1;
		}
		else
		{
			cout << "Comment :=>> M2 XARXACOM CALCULAT ERROR : Esperavem:" << OKM2[0] << endl;
			valid = false;
		}

		cout << "Comment :=>> ======================================" << endl;
		cout << "Comment :=>> CALCULANT K XARXACOM.................." << endl;
		cXarxaCom.calculaK();
		vector<int> vKXarxaCom = cXarxaCom.getK();
		ofstream fKXarxaCom, fKXarxaComOK;
			
		if (comparaVectInt(vKXarxaCom,"0KXarxaCom.txt","0KXarxaComOK.txt", "0KXarxaComCOMP.txt"))
		{
			cout << "Comment :=>> K XARXACOM CALCULAT OK ..............." << endl;
			grade+=0.5;
		}
		else
		{
			cout << "Comment :=>> K XARXACOM CALCULAT ERROR............." << endl;
			valid = false;
		}
			

		cout << "Comment :=>> ======================================" << endl;
		cout << "Comment :=>> CALCULANT A XARXACOM.................." << endl;
		cXarxaCom.calculaA();
		vector<double> vAXarxaCom = cXarxaCom.getA();
		if (comparaVectDoub(vAXarxaCom, "0AXarxaCom.txt", "0AXarxaComOK.txt", "0AXarxaComCOMP.txt"))
		{
			cout << "Comment :=>> A XARXACOM CALCULAT OK ..............." << endl;
			grade+=0.6;
		}
		else
		{
			cout << "Comment :=>> A XARXACOM CALCULAT ERROR............." << endl;
				valid = false;
		}

		cout << "Comment :=>> ======================================" << endl;
		cout << "Comment :=>> CALCULANT deltaQ i HeapTotal.........." << endl;
		cXarxaCom.creaDeltaQHeap();
			
		cout << "Comment :=>> VALIDANT deltaQ ......................" << endl;
		vector<map<pair<int, int>, double>> vDeltaQXaxaCom = cXarxaCom.getdeltaQ();
		if (comparaVectMap(vDeltaQXaxaCom, "0DeltaQXarxaCom.txt", "0DeltaQXarxaComOK.txt", "0DeltaQXarxaComCOMP.txt"))
		{
			cout << "Comment :=>> DeltaQ XARXACOM CALCULAT OK .........." << endl;
			grade+=3;
		}
		else
		{
			cout << "Comment :=>> DeltaQ XARXACOM CALCULAT ERROR........" << endl;
			valid = false;
		}
		cout << "Comment :=>> VALIDANT HeapTotal ..................." << endl;
		Heap hXarxaCom = cXarxaCom.gethTotal();

		if (comparaHeap(hXarxaCom, "0HXarxaCom.txt", "0HXarxaComOK.txt", "0HXarxaComCOMP.txt"))
		{
			cout << "Comment :=>> HeapTotal XARXACOM CALCULAT OK ......." << endl;
			grade+=0.5;
		}
		else
		{
			cout << "Comment :=>> HeapTotal XARXACOM CALCULAT ERROR....." << endl;
			valid = false;
		}

		cout << "Comment :=>> ======================================" << endl;
		cout << "Comment :=>> CALCULANT IndexComs..................." << endl;
		cXarxaCom.creaIndexComs();
		vector<pair<int, int>> vindexComsXarxaCom = cXarxaCom.getIndexComs();
		if (comparaVectPair(vindexComsXarxaCom, "0IndexComsXarxaCom.txt", "0IndexComsXarxaComOK.txt", "0IndexComsXarxaComCOMP.txt"))
		{
			cout << "Comment :=>> IndexComs XARXACOM CALCULAT OK ......." << endl;
			grade+=0.3;
		}
		else
		{
			cout << "Comment :=>> IndexComs XARXACOM CALCULAT ERROR....." << endl;
			valid = false;
		}

		mXarxaCom.clear();
		cXarxaCom.clear();
		vKXarxaCom.clear();
		vAXarxaCom.clear();
		hXarxaCom.clear();
		vDeltaQXaxaCom.clear();
		vindexComsXarxaCom.clear();

		cout << "Comment :=>> ==========================================" << endl;
		cout << "Comment :=>> CREANT GRAF XARXACOM......................" << endl;
		Graph gXarxaCom(nomFitxer);

		cout << "Comment :=>> ==========================================" << endl;
		cout << "Comment :=>> ESCRIVINT XARXACOM........................" << endl;
		// cout << gXarxaCom;

		cout << "Comment :=>> ==========================================" << endl;
		cout << "Comment :=>> CALCULANT COMUNITATS XARXACOM............." << endl;
		cout << "Comment :=>> ==========================================" << endl;

		list<Tree<double>*> listDendrogramsXarxaCom;
		gXarxaCom.calculaComunitats(listDendrogramsXarxaCom);

		cout << "Comment :=>> ==========================================" << endl;
		cout << "Comment :=>> ESCRIVINT COMUNITATS XARXACOM............." << endl;
		cout << "Comment :=>> ==========================================" << endl;
		ofstream fCOMXarxaCom, fCOMXarxaComOK;
		fCOMXarxaCom.open("0COMXarxaCom.txt");
		if (fCOMXarxaCom.is_open())
		{
			list<Tree<double>*>::iterator itAnt;
			list<Tree<double>*>::iterator it;
			it = listDendrogramsXarxaCom.begin();
			while (it != listDendrogramsXarxaCom.end())
			{
				fCOMXarxaCom << (*(*it)) << endl;
				cout << (*(*it)) << endl;
				itAnt = it;
				it++;
				listDendrogramsXarxaCom.erase(itAnt);
			}
			fCOMXarxaCom.close();
		}
		if (IgualFitxers("0COMXarxaCom.txt", "0COMXarxaComOK.txt", "0COMXarxaComComp.txt"))
		{
			cout << "Comment :=>> COMUNITATS XARXACOM CALCULAT OK .........." << endl;
			grade+=5;
		}
		else
		{
			cout << "Comment :=>> COMUNITATS XARXACOM CALCULAT ERROR........" << endl;
			valid = false;
		}
		gXarxaCom.clear();

		cout << endl << "Comment :=>> GRADE Parcial: " << grade << "(Sobre 10)" << endl << endl;

		cout << "Comment :=>> =============================================================" << endl;
		cout << "Comment :=>> TEST SOBRE ZACKARY..........................................." << endl;
		cout << "Comment :=>> =============================================================" << endl;
		string nomFitxerZack = "ZackaryKarate.txt";

		cout << "Comment :=>> =============================================================" << endl;
		cout << "Comment :=>> LLEGINT I CREANT MATRIU I COMUNITAT ZACKARY.................." << endl;
		MatriuSparse mXarxaZack(nomFitxerZack);
		Comunitat cXarxaZack(&mXarxaZack);

		cout << "Comment :=>> ========================================" << endl;
		cout << "Comment :=>> CALCULANT M2 XARXAZACK.................." << endl;
		cXarxaZack.calculaM2();
		int m2XarxaZack = cXarxaZack.getM2();
		cout << "Comment :=>> M2 CALCULAT: " << m2XarxaZack << endl;
		if (m2XarxaZack == OKM2[1])
		{
			cout << "Comment :=>> M2 XARXAZACK CALCULAT OK ..............." << endl;
			grade += 0.1;
		}
		else
		{
			cout << "Comment :=>> M2 XARXAZACK CALCULAT ERROR : Esperavem:" << OKM2[0] << endl;
			valid = false;
		}

		cout << "Comment :=>> ========================================" << endl;
		cout << "Comment :=>> CALCULANT K ZACKARY....................." << endl;
		cXarxaZack.calculaK();
		vector<int> vKXarxaZack = cXarxaZack.getK();
		ofstream fKXarxaZack, fKXarxaZackOK;

		if (comparaVectInt(vKXarxaZack, "0KZackary.txt", "0KZackaryOK.txt", "0KZackaryCOMP.txt"))
		{
			cout << "Comment :=>> K ZACKARY CALCULAT OK .................." << endl;
			grade += 0.5;
		}
		else
		{
			cout << "Comment :=>> K ZACKARY CALCULAT ERROR................" << endl;
			valid = false;
		}

		cout << "Comment :=>> ========================================" << endl;
		cout << "Comment :=>> CALCULANT A ZACKARY....................." << endl;
		cXarxaZack.calculaA();
		vector<double> vAXarxaZack = cXarxaZack.getA();
		if (comparaVectDoub(vAXarxaZack, "0AZackary.txt", "0AZackaryOK.txt", "0AZackaryCOMP.txt"))
		{
			cout << "Comment :=>> A ZACKARY CALCULAT OK .................." << endl;
			grade += 0.6;
		}
		else
		{
			cout << "Comment :=>> A ZACKARY CALCULAT ERROR................" << endl;
			valid = false;
		}

		cout << "Comment :=>> ========================================" << endl;
		cout << "Comment :=>> CALCULANT deltaQ i HeapTotal............" << endl;
		cXarxaZack.creaDeltaQHeap();

		cout << "Comment :=>> VALIDANT deltaQ ........................" << endl;
		vector<map<pair<int, int>, double>> vDeltaQXaxaZack = cXarxaZack.getdeltaQ();
		if (comparaVectMap(vDeltaQXaxaZack, "0DeltaQZackary.txt", "0DeltaQZackaryOK.txt", "0DeltaQZackaryCOMP.txt"))
		{
			cout << "Comment :=>> DeltaQ ZACKARY CALCULAT OK ............." << endl;
			grade += 3;
		}
		else
		{
			cout << "Comment :=>> DeltaQ ZACKARY CALCULAT ERROR..........." << endl;
			valid = false;
		}
		cout << "Comment :=>> VALIDANT HeapTotal ....................." << endl;
		Heap hXarxaZack = cXarxaZack.gethTotal();

		if (comparaHeap(hXarxaZack, "0HZackary.txt", "0HZackaryOK.txt", "0HZackaryCOMP.txt"))
		{
			cout << "Comment :=>> HeapTotal ZACKARY CALCULAT OK .........." << endl;
			grade += 0.5;
		}
		else
		{
			cout << "Comment :=>> HeapTotal ZACKARY CALCULAT ERROR........" << endl;
			valid = false;
		}

		cout << "Comment :=>> ========================================" << endl;
		cout << "Comment :=>> CALCULANT IndexComs....................." << endl;
		cXarxaZack.creaIndexComs();
		vector<pair<int, int>> vindexComsXarxaZack = cXarxaZack.getIndexComs();
		if (comparaVectPair(vindexComsXarxaZack, "0IndexComsZackary.txt", "0IndexComsZackaryOK.txt", "0IndexComsZackaryCOMP.txt"))
		{
			cout << "Comment :=>> IndexComs ZACKARY CALCULAT OK .........." << endl;
			grade += 0.3;
		}
		else
		{
			cout << "Comment :=>> IndexComs ZACKARY CALCULAT ERROR........" << endl;
			valid = false;
		}
		mXarxaZack.clear();
		cXarxaZack.clear();
		vKXarxaZack.clear();
		vAXarxaZack.clear();
		hXarxaZack.clear();
		vDeltaQXaxaZack.clear();
		vindexComsXarxaZack.clear();

		cout << "Comment :=>> ==============================================" << endl;
		cout << "Comment :=>> CREANT GRAF ZACKARY..........................." << endl;
		Graph gZack(nomFitxerZack);

		cout << "Comment :=>> ==============================================" << endl;
		cout << "Comment :=>> ESCRIVINT ZACKARY............................." << endl;
		// cout << gZack;

		cout << "Comment :=>> ==============================================" << endl;
		cout << "Comment :=>> CALCULANT COMUNITATS ZACKARY.................." << endl;
		cout << "Comment :=>> ==============================================" << endl;
			
		list<Tree<double>*> listDendrogramsZack;
		gZack.calculaComunitats(listDendrogramsZack);

		cout << "Comment :=>> ==============================================" << endl;
		cout << "Comment :=>> ESCRIVINT COMUNITATS ZACKARY.................." << endl;
		cout << "Comment :=>> ==============================================" << endl;
		ofstream fCOMZack, fCOMZackOK;
		fCOMZack.open("0COMZack.txt");
		if (fCOMZack.is_open())
		{
			list<Tree<double>*>::iterator itAnt;
			list<Tree<double>*>::iterator it;
			it = listDendrogramsZack.begin();
			while (it != listDendrogramsZack.end())
			{
				fCOMZack << (*(*it)) << endl;
				cout << (*(*it)) << endl;
				itAnt = it;
				it++;
				listDendrogramsZack.erase(itAnt);
			}

			fCOMZack.close();
		}

		if (IgualFitxers("0COMZack.txt", "0COMZackOK.txt", "0COMZackComp.txt"))
		{
			cout << "Comment :=>> COMUNITATS ZACKARY CALCULAT OK ..............." << endl;
			grade += 5;
		}
		else
		{
			cout << "Comment :=>> COMUNITATS ZACKARY CALCULAT ERROR............." << endl;
			valid = false;
		}
		gZack.clear();

		cout << endl << "Comment :=>> GRADE Parcial: " << grade << "(Sobre 20)" <<endl << endl;

			
		cout << "Comment :=>> ==========================================" << endl;
		cout << "Comment :=>> TEST SOBRE EPINIONS SIMETRIC............. " << endl;
		cout << "Comment :=>> ==========================================" << endl;
		string nomFitxerEpi = "EpinionsSimetricOrdenat.txt";

		cout << "Comment :=>> =============================================================" << endl;
		cout << "Comment :=>> LLEGINT I CREANT MATRIU I COMUNITAT EPINIONS................." << endl;
		MatriuSparse mXarxaEpi(nomFitxerEpi);
		Comunitat cXarxaEpi(&mXarxaEpi);

		cout << "Comment :=>> ========================================" << endl;
		cout << "Comment :=>> CALCULANT M2 EPINIONS..................." << endl;
		cXarxaEpi.calculaM2();
		int m2XarxaEpi = cXarxaEpi.getM2();
		cout << "Comment :=>> M2 CALCULAT: " << m2XarxaEpi << endl;
		if (m2XarxaEpi == OKM2[2])
		{
			cout << "Comment :=>> M2 EPINIONS CALCULAT OK ................" << endl;
			grade += 0.1;
		}
		else
		{
			cout << "Comment :=>> M2 EPINIONS CALCULAT ERROR : Esperavem:." << OKM2[0] << endl;
			valid = false;
		}

		cout << "Comment :=>> ========================================" << endl;
		cout << "Comment :=>> CALCULANT K EPINIONS...................." << endl;
		cXarxaEpi.calculaK();
		vector<int> vKXarxaEpi = cXarxaEpi.getK();
		ofstream fKXarxaEpi, fKXarxaEpiOK;

		if (comparaVectInt(vKXarxaEpi, "0KEpinions.txt", "0KEpinionsOK.txt", "0KEpinionsCOMP.txt"))
		{
			cout << "Comment :=>> K EPINIONS CALCULAT OK ................." << endl;
			grade += 0.5;
		}
		else
		{
			cout << "Comment :=>> K EPINIONS CALCULAT ERROR..............." << endl;
			valid = false;
		}

		cout << "Comment :=>> ========================================" << endl;
		cout << "Comment :=>> CALCULANT A EPINIONS...................." << endl;
		cXarxaEpi.calculaA();
		vector<double> vAXarxaEpi = cXarxaEpi.getA();
		if (comparaVectDoub(vAXarxaEpi, "0AEpinions.txt", "0AEpinionsOK.txt", "0AEpinionsCOMP.txt"))
		{
			cout << "Comment :=>> A EPINIONS CALCULAT OK ................." << endl;
			grade += 0.6;
		}
		else
		{
			cout << "Comment :=>> A EPINIONS CALCULAT ERROR..............." << endl;
			valid = false;
		}

		cout << "Comment :=>> ========================================" << endl;
		cout << "Comment :=>> CALCULANT deltaQ i HeapTotal............" << endl;
		cXarxaEpi.creaDeltaQHeap();

		cout << "Comment :=>> VALIDANT deltaQ ........................" << endl;
		vector<map<pair<int, int>, double>> vDeltaQXaxaEpi = cXarxaEpi.getdeltaQ();
		if (comparaVectMap(vDeltaQXaxaEpi, "0DeltaQEpinions.txt", "0DeltaQEpinionsOK.txt", "0DeltaQEpinionsCOMP.txt"))
		{
			cout << "Comment :=>> DeltaQ EPINIONS CALCULAT OK ............" << endl;
			grade += 3;
		}
		else
		{
			cout << "Comment :=>> DeltaQ EPINIONS CALCULAT ERROR.........." << endl;
			valid = false;
		}
		cout << "Comment :=>> VALIDANT HeapTotal ....................." << endl;
		Heap hXarxaEpi = cXarxaEpi.gethTotal();

		if (comparaHeap(hXarxaEpi, "0HEpinions.txt", "0HEpinionsOK.txt", "0HEpinionsCOMP.txt"))
		{
			cout << "Comment :=>> HeapTotal EPINIONS CALCULAT OK ........." << endl;
			grade += 0.5;
		}
		else
		{
			cout << "Comment :=>> HeapTotal EPINIONS CALCULAT ERROR......." << endl;
			valid = false;
		}

		cout << "Comment :=>> ========================================" << endl;
		cout << "Comment :=>> CALCULANT IndexComs....................." << endl;
		cXarxaEpi.creaIndexComs();
		vector<pair<int, int>> vindexComsXarxaEpi = cXarxaEpi.getIndexComs();
		if (comparaVectPair(vindexComsXarxaEpi, "0IndexComsEpinions.txt", "0IndexComsEpinionsOK.txt", "0IndexComsEpinionsCOMP.txt"))
		{
			cout << "Comment :=>> IndexComs EPINIONS CALCULAT OK ........." << endl;
			grade += 0.3;
		}
		else
		{
			cout << "Comment :=>> IndexComs EPINIONS CALCULAT ERROR......." << endl;
			valid = false;
		}
		
		mXarxaEpi.clear();
		cXarxaEpi.clear();
		vKXarxaEpi.clear();
		vAXarxaEpi.clear();
		hXarxaEpi.clear();
		vDeltaQXaxaEpi.clear();
		vindexComsXarxaEpi.clear();

		cout << "Comment :=>> ====================================================" << endl;
		cout << "Comment :=>> ATENCIO NO CALCULEM COMUNITATS EPINIONS............." << endl;
		cout << "Comment :=>> ====================================================" << endl;
		cout << endl << "Comment :=>> GRADE Parcial: " << grade << "(Sobre 25)" << endl << endl;
		
		
	
		if (valid)
			cout << "Comment :=>> Final del test sense errors" << endl;
		if (grade < 0)
			grade = 0;
		cout << endl << "Grade :=>> " << grade << endl;

		system("pause");
		return 0;
	}
	catch (std::bad_alloc)
	{
		cout << "Comment ==> error allocatant memoria:" << endl;
	}
	catch (const std::out_of_range& oor) {
		std::cerr << "Out of Range error: " << oor.what() << '\n';
	}
	catch (const char* msg)
	{
		cout << msg << endl;
	}

}

