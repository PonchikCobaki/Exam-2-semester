#include <iostream>
#include <list>
#include <iterator>
#include <string>
#include <fstream>

using namespace std;

void NaturalMergeSort(std::list<double>& data);
void ReadBinFile(std::string dir, std::list<double>& data);
void WriteBinFile(std::string dir, std::list<double>& data);
void RandomData(std::list<double>& data);

void main(){
	
	list<double> data;
	RandomData(data);
	WriteBinFile("rnd_data.bin", data);
	ReadBinFile("rnd_data.bin", data);
	cout << "reading data" << endl;
	uint32_t count(0);
	for (double i : data) {
		cout << i << "\t";

		// Если вывели 5 чисел, то вставляем символ новой строки
		if ((count + 1) % 5 == 0)
			std::cout << "\n";
		++count;
	}
}

void ReadBinFile(std::string dir, std::list<double>& data) {

	ifstream inBinFile(dir, ios::binary);
	if (!inBinFile) {
		cerr << "Error opening input buffer file on time reading" << endl;
		system("pause");
	}

	uint32_t dataCount = inBinFile.seekg(0, ios::end).tellg() /	sizeof(double);
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

void WriteBinFile(std::string dir, std::list<double>& data) {

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

void RandomData(std::list<double>& data) {
	srand(static_cast<unsigned int>(time(0)));
	uint32_t n;
	cin >> n;
	for (int count = 0; count < n; ++count)
	{
		double val = rand() / 100.;
		data.push_back(val);
		std::cout << val << "\t";

		// Если вывели 5 чисел, то вставляем символ новой строки
		if ((count + 1) % 5 == 0)
			std::cout << "\n";
	}
}