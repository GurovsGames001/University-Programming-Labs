#include <iostream>
#include <vector>

struct PairIndexes
{
	PairIndexes(unsigned int a, unsigned int b) : lP(a), rP(b) {};
	unsigned int lP;
	unsigned int rP;
};

void readAndWriteFile(std::istream& in_stream, std::ostream& out_stream);

int select(std::vector<int>& a, unsigned int firstIndex, unsigned int lastIndex, unsigned int k);
PairIndexes split(std::vector<int>& a, unsigned int firstIndex, unsigned int lastIndex, int p);

int main()
{
	readAndWriteFile(std::cin, std::cout);
	
	return 0;
}

void readAndWriteFile(std::istream& inStream, std::ostream& outStream)
{
	/*int lengthArray = 8;
	std::vector<int> a = { 5, 3, 2, 7, 8, 3, 5, 9 };
	int anyElementArray = 5;*/
	unsigned int lengthArray = 0;
	inStream >> lengthArray;

	int elementArray = 0;
	std::vector<int> a;
	for (unsigned int i = 0; i < lengthArray; i++)
	{
		inStream >> elementArray;
		a.push_back(elementArray);
	}

	int anyElementArray = 0;
	inStream >> anyElementArray;

	PairIndexes pair = split(a, 0, lengthArray - 1, anyElementArray);

	for (unsigned int k = 0; k < a.size(); k++)
	{
		outStream << a[k] << " ";
	}
	outStream << std::endl;

	outStream << pair.lP << " " << pair.rP << std::endl;

	outStream << "median: " << select(a, 0, lengthArray - 1, (lengthArray - 1) / 2) << std::endl;
}

int select(std::vector<int>& a, unsigned int firstIndex, unsigned int lastIndex, unsigned int k)
{
	// Вход: массив a[0..n - 1] из натуральных чисел;
	//		 целые числа firstIndex и lastIndex, такие что 0 <= firstIndex <= lastIndex <= n - 1;
	//		 целое число k, такое что 0 <= k <= n - 1.
	// Выход: k-я порядковая статистика массива a.

	if (firstIndex <= lastIndex)
	{
		srand(time(0));
		int p = a[firstIndex + (rand() % (lastIndex - firstIndex + 1))];

		// Делим массив относительно элемента, стоящего в центре массива a
		//int p = a[(firstIndex + lastIndex) / 2];
		PairIndexes pairIndexes = split(a, firstIndex, lastIndex, p);

		if (k < pairIndexes.lP)
		{
			return select(a, firstIndex, pairIndexes.lP - 1, k);
		}
		else if (k <= pairIndexes.rP)
		{
			return p;
		}
		return select(a, pairIndexes.rP + 1, lastIndex, k - pairIndexes.rP);
	}
	return a[firstIndex + k];
}

PairIndexes split(std::vector<int>& a, unsigned int firstIndex, unsigned int lastIndex, int p)
{
	// Вход: массив a[0..n - 1] из натуральных чисел;
	//		 целые числа firstIndex и lastIndex, такие что 0 <= firstIndex <= lastIndex <= n - 1;
	//		 натуральное число p, такое что p принадлежит массиву a.
	// Выход: 1) целые числа lP и rP, такие что 0 <= lP <= rP <= n - 1;
	//		  2) все элементы подмассива a[firstIndex..lP - 1] меньше p;
	//		  3) все элементы подмассива a[lP..rP] равны p;
	//		  4) все элементы подмассива a[rP + 1..lastIndex] больше p;
	//		  5) a[firstIndex], a[firstIndex + 1], ..., a[lastIndex] - это перестановка элементов
	//			 входного подмассива a[firstIndex..lastIndex];
	//		  6) подмассивы a[0..firstIndex - 1] и a[lastIndex + 1..n - 1] совпадают
	//			 с соответствующими подмассивами входного массива a[0..n - 1].

	int i = firstIndex - 1; // Индекс последнего элемента в подмассиве элементов, меньших p
	int j = firstIndex - 1; // Индекс последнего элемента в подмассиве элементов, равных p
	unsigned int k = firstIndex;

	for (k; k <= lastIndex; k++)
	{
		if (a[k] < p)
		{
			i++;
			j++;

			std::swap(a[j], a[k]);
			std::swap(a[i], a[j]);
		}
		else if (a[k] == p)
		{
			j++;

			std::swap(a[j], a[k]);
		}
	}

	PairIndexes pairIndexes(i + 1, j);

	return pairIndexes;
}