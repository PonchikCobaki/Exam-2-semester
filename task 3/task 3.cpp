#include <iostream>
#include <list>
#include <iterator>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

using mergeFnc = void(*)(std::vector<double>& data, int l, int m, int r);
using arrayWalkintFnc = int(*)(std::vector<double>& data, mergeFnc Merge, uint32_t l, uint32_t r);

void NaturalMergeSort(std::vector<double>& data, mergeFnc Merge, arrayWalkintFnc ArrayWalk, uint32_t l, uint32_t r);
int ArrayWalk(std::vector<double>& data, mergeFnc Merge, uint32_t l, uint32_t r);
void Merge(std::vector<double>& data, int l, int m, int r);

void ReadBinFile(std::string dir, std::vector<double>& data);
void WriteBinFile(std::string dir, std::vector<double>& data);
void RandomData(std::vector<double>& data);

void main() {
	string dir = "rnd_data.bin";
	/*cout << "enter the file directory" << endl;
	getline(cin, dir);*/

	vector<double> data;
	RandomData(data);


	//ReadBinFile(dir, data);
	//cout << "reading data" << endl;
	uint32_t count(0);
	//for (double i : data) {
	//	cout << i << "\t";

	//	// Если вывели 5 чисел, то вставляем символ новой строки
	//	if ((count + 1) % 5 == 0)
	//		std::cout << "\n";
	//	++count;
	//}

	NaturalMergeSort(data, Merge, ArrayWalk, 0, data.size() - 1);

	count = 0;
	std::cout << "\n";
	cout << "sorted data" << endl;
	for (double i : data) {
		cout << i << "\t";

		// Если вывели 5 чисел, то вставляем символ новой строки
		if ((count + 1) % 5 == 0)
			std::cout << "\n";
		++count;
	}
	WriteBinFile(dir, data);
}

// основная функция сортировки
void NaturalMergeSort(std::vector<double>& data, mergeFnc Merge, arrayWalkintFnc ArrayWalk, uint32_t l, uint32_t r) {

	uint32_t depth(0), prevDepth(0);	// количество слияний

	depth = ArrayWalk(data, Merge, l, r);

	while (depth != prevDepth) {
		prevDepth = depth;
		depth = ArrayWalk(data, Merge, l, r);
	}
}

// функция прохода по массиву и слияния двух соседних подмассивов
int ArrayWalk(std::vector<double>& data, mergeFnc Merge, uint32_t l, uint32_t r) {
	int64_t m(0), rCur(0), depth(0);

	// поиск подмассива массива 
	while (l < r && rCur < r && depth <= 0) {
		depth = 0;
		int counter(0);
		for (uint32_t i = l; i < r && counter != 2; ++i) {
			if (data[i] > data[i + 1]) {
				if (!counter) {
					m = i;
					++counter;
				}
				else {
					rCur = i;
					++counter;
				}
			}
			else if (i + 1 == r) {
				rCur = r;
				++counter;
			}

		}
		cout << "\ndata: ";
		for (double i : data) {
			cout << i << "\t";
		}
		// дальнейшее слияние или выход
		if (l <= m) {
			Merge(data, l, m, rCur);
			l = rCur + 1;
			m = 0;
			depth = ArrayWalk(data, Merge, l, r);
			return depth + 1;
		}
		else if (rCur == data.size() - 1) {
			break;
		}
		else {
			break;
		}

	}


}

// функция слияния двух массивов
void Merge(std::vector<double>& data, int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	// создание буфферов
	vector<double> L, R;
	L.resize(n1);
	R.resize(n2);
	// коппирование данных в буферы
	for (i = 0; i < n1; i++)
		L[i] = data[l + i];
	for (j = 0; j < n2; j++)
		R[j] = data[m + 1 + j];

	// слияние подмассивов в основнойы
	i = 0; // индекс для первого подмассива
	j = 0; // индекс для второго подмасиива
	k = l; // индекс для итогового массива
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			data[k] = L[i];
			i++;
		}
		else {
			data[k] = R[j];
			j++;
		}
		k++;
	}

	// дальнейшее копирование на случай если первый и второй подмассив разной длинны
	while (i < n1) {
		data[k] = L[i];
		i++;
		k++;
	}


	while (j < n2) {
		data[k] = R[j];
		j++;
		k++;
	}
}


//	чтение бинарного файла
void ReadBinFile(std::string dir, std::vector<double>& data) {

	ifstream inBinFile(dir, ios::binary);
	if (!inBinFile) {
		cerr << "Error opening input buffer file on time reading" << endl;
		system("pause");
	}

	uint32_t dataCount = inBinFile.seekg(0, ios::end).tellg() / sizeof(double);
	inBinFile.seekg(0, ios::beg);
	double buffer;
	data.clear();

	for (uint32_t i = 0; i < dataCount; ++i) {
		// чтение в массив
		inBinFile.read((char*)&buffer, sizeof(double));
		data.push_back(buffer);
	}

	inBinFile.close();

}

//	запись в бинарный файл
void WriteBinFile(std::string dir, std::vector<double>& data) {

	ofstream outBinFile(dir, ios::binary);
	if (!outBinFile) {
		cerr << "Error opening input buffer file on time writing" << endl;
		system("pause");
	}

	for (double i : data) {
		// запись в файл
		outBinFile.write((char*)&i, sizeof(double));
	}

	outBinFile.close();

}

//	генератор данных
void RandomData(std::vector<double>& data) {
	srand(static_cast<unsigned int>(time(0)));
	uint32_t n;
	cin >> n;
	for (int count = 0; count < n; ++count)
	{
		double val = rand() / 100;
		data.push_back(val);
		std::cout << val << "\t";

		// Если вывели 5 чисел, то вставляем символ новой строки
		if ((count + 1) % 5 == 0)
			std::cout << "\n";
	}
}