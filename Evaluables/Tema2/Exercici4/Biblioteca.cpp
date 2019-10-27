#include "Biblioteca.h"

void Biblioteca::llegirPublicacions(const string& nomFitxer)
{
	string line, tok;
	ifstream fitxer;
	fitxer.open(nomFitxer);

	if (fitxer.is_open())
	{
		Llibre* l = nullptr;
		Revista* r = nullptr;
		char mode = 'N';
		int count = 0, exemplars = 0;
		try
		{
			while (getline(fitxer, line))
			{
				if (line[line.size() - 1] == '\r' || line[line.size() - 1] == ' ')
					line = line.substr(0, line.size() - 1);

				switch (line[0])
				{
				case 'L':
					if (count == 0) {
						switch (mode)
						{
						case 'L':
							publicacions.push_back(l);
							break;
						case 'R':
							publicacions.push_back(r);
							break;
						default:
							break;
						}
						mode = 'L';
						count = 5;
						l = new Llibre;
						break;
					}
				case 'R':
					if (count == 0) {
						switch (mode)
						{
						case 'L':
							publicacions.push_back(l);
							break;
						case 'R':
							publicacions.push_back(r);
							break;
						default:
							break;
						}
						mode = 'R';
						count = 5;
						r = new Revista;
						break;
					}
				default:
					switch (mode)
					{
					case 'L':
						switch (count)
						{
						case 5:
							l->setCodi(line);
							break;
						case 4:
							l->setTitol(line);
							break;
						case 3:
							l->setAutor(line);
							break;
						case 2:
							l->setCopies(stoi(line));
							break;
						case 1:
							l->setDiesPrestec(stoi(line));
							break;
						default:
							break;
						}
						break;
					case 'R':
						switch (count)
						{
						case 5:
							r->setCodi(line);
							break;
						case 4:
							r->setTitol(line);
							break;
						case 3:
							r->setPeriodicitat(line);
							break;
						case 2:
							exemplars = stoi(line);
							if (exemplars == 0) count = 1;
							break;
						case 1:
							for (int i = 0; i < exemplars && i < line.size(); i++)
							{
								if (line[i] != ' ')
									tok += line[i];
								else
								{
									r->addExemplar(stoi(tok));
									tok = "";
								}
							}
							r->addExemplar(stoi(tok));
							tok = "";
						default:
							break;
						}
						break;
					default:
						break;
					}
					count--;
					break;
				}
			}
			switch (mode)
			{
			case 'L':
				publicacions.push_back(l);
				break;
			case 'R':
				publicacions.push_back(r);
				break;
			default:
				break;
			}
		}
		catch (exception e) { cout << "An error has occurred: " << e.what(); }
		fitxer.close();
	}
}

bool Biblioteca::prestar(const string& idUsuari, const string& codi, const Data& dataPrestec, Data& dataRetorn, int nExemplar)
{
	bool success = false;
	int dies = 0, copies = 0;

	for (auto it = publicacions.begin(); it != publicacions.end(); it++)
	{
		if ((*it)->getCodi() == codi)
		{
			dies = (*it)->getDiesPrestec();
			if ((*it)->esLlibre())
			{
				copies = ((Llibre*)*it)->getCopies();
				success = true;
			}
			else
				success = (((Revista*)*it)->getNombreExemplars() != 0 && ((Revista*)*it)->trobarExemplar(nExemplar));
			break;
		}
	}

	if (success) 
	{
		int actius = 0;
		for (auto it = prestecs.begin(); it != prestecs.end(); it++)
		{
			if (it->getCodi() == codi)
			{
				if (nExemplar == 0)
				{
					actius++;
					if (actius >= copies)
					{
						success = false;
						break;
					}
				}
				else if (it->getExemplar() == nExemplar)
				{
					success = false;
					break;
				}
			}
		}
	}
	

	if (success)
	{
		Data devolucio(dataPrestec);
		devolucio = devolucio + dies;
		dataRetorn = devolucio;
		Prestec* nou_prestec = new Prestec(idUsuari, codi, dataPrestec, devolucio, nExemplar);
		prestecs.push_back(*nou_prestec);
	}

	return success;
}

bool Biblioteca::retornar(const string& idUsuari, const string& codi, const Data& data, bool& dataCorrecta, int nExmplar)
{
	bool success = false;

	for (auto it = prestecs.begin(); it != prestecs.end(); it++)
	{
		if (it->getCodi() == codi && it->getUsuari() == idUsuari && it->getExemplar() == nExmplar)
		{
			dataCorrecta = (data < it->getDataRetorn() || data == it->getDataRetorn());
			success = true;
			prestecs.erase(it);
			break;
		}
	}

	return success;
}
