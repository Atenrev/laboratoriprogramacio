#include <vector>
using namespace std;

int particio(vector<int>& v, int indexInici, int indexFinal)
{
	int pivot = v[indexFinal];
	int i = indexInici - 1;

	int temp;
	for (int j = indexInici; j < indexFinal; j++)
	{
		if (v[j] < pivot)
		{
			i++;
			swap(v[i], v[j]);
		}
	}

	swap(v[i + 1], v[indexFinal]);
	return i + 1;
}

void quicksort(vector<int>& v, int indexInici, int indexFinal)
{
	if (indexInici < indexFinal)
	{
		int pi = particio(v, indexInici, indexFinal);

		quicksort(v, indexInici, pi - 1);
		quicksort(v, pi + 1, indexFinal);
	}
}