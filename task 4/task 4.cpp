#include <iostream>
#include <list>
#include <iterator>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

using mergeFnc = void(*)(std::vector<double>& data, int l, int m, int r);

void NaturalMergeSort(std::vector<double>& data, mergeFnc Merge);
void Merge(std::vector<double>& data, int l, int m, int r);
void ReadBinFile(std::string dir, std::vector<double>& data);
void WriteBinFile(std::string dir, std::vector<double>& data);
void RandomData(std::vector<double>& data);

void main() {

	//vector<double> data = { 8, 3, 4, 2, 5, 1, 1, 0, 7, 8, 55 };
	//vector<double> data = { 223.6,   49.78,   320.41,  155.2,   174.89, 264.16,  276.97 };
	//vector<double> data = { 90,      75,     100,     28,      36 };
	vector<double> data;
	RandomData(data);
	//WriteBinFile("rnd_data.bin", data);
	//ReadBinFile("rnd_data.bin", data);
	//cout << "reading data" << endl;
	uint32_t count(0);
	//for (double i : data) {
	//	cout << i << "\t";

	//	// Если вывели 5 чисел, то вставляем символ новой строки
	//	if ((count + 1) % 5 == 0)
	//		std::cout << "\n";
	//	++count;
	//}

	NaturalMergeSort(data, Merge);
	count = 0;
	std::cout << "\n";
	for (double i : data) {
		cout << i << "\t";

		// Если вывели 5 чисел, то вставляем символ новой строки
		if ((count + 1) % 5 == 0)
			std::cout << "\n";
		++count;
	}
}

void NaturalMergeSort(std::vector<double>& data, mergeFnc Merge) {
	vector<uint32_t> subArrEnds;	// массив индексов конца подмассивов
	for (uint32_t i = 0; i < (data.size() - 1); ++i) {
		if (data[i] > data[i + 1]) {
			subArrEnds.push_back(i);
		}
	}
	subArrEnds.push_back(data.size() - 1);	// последний подмассив
	for (auto i : subArrEnds) {
		cout << i << " ";
	}
	cout << endl;

	uint32_t pairNum(1);
	int64_t l(0), m = subArrEnds[pairNum * 2 - 2], r = subArrEnds[pairNum * 2 - 1];
	while (subArrEnds.size() > 1) {
		Merge(data, l, m, r);
		if (pairNum * 2 + 1 >= subArrEnds.size()) {
			int delCount = subArrEnds.size() / 2;
			for (int i(0); i < delCount; i += 2) {
				subArrEnds.erase(subArrEnds.begin() + pairNum * 2 - 2);
				--i;
			}
			pairNum = 0;
		}
			
		++pairNum;
		if (pairNum == 1) {
			l = 0;
		}
		else {
			l = r;
		}
		if (subArrEnds.size() > 1){
			m = subArrEnds[pairNum * 2 - 2], r = subArrEnds[pairNum * 2 - 1];
		}
	}
}

void Merge(std::vector<double>& data, int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	vector<double> L, R;
	L.resize(n1);
	R.resize(n2);
	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = data[l + i];
	for (j = 0; j < n2; j++)
		R[j] = data[m + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray
	j = 0; // Initial index of second subarray
	k = l; // Initial index of merged subarray
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

	/* Copy the remaining elements of L[], if there
	are any */
	while (i < n1) {
		data[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	are any */
	while (j < n2) {
		data[k] = R[j];
		j++;
		k++;
	}
	cout << "merge array: " << endl;
	for (auto i : data) {
		cout << i << " ";
	}
	cout << endl;
}



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

void RandomData(std::vector<double>& data) {
	srand(static_cast<unsigned int>(time(0)));
	uint32_t n;
	cin >> n;
	for (int count = 0; count < n; ++count)
	{
		double val = rand() % 101;
		data.push_back(val);
		std::cout << val << "\t";

		// Если вывели 5 чисел, то вставляем символ новой строки
		if ((count + 1) % 5 == 0)
			std::cout << "\n";
	}
}