#include <iostream>
#include <list>
#include <iterator>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

using mergeFnc = void(*)(std::vector<double>& data, vector<uint32_t> subArrEnds, uint32_t pairNum, uint32_t prevInd);

void NaturalMergeSort(std::vector<double>& data, mergeFnc Merge);
void Merge(std::vector<double>& data, vector<uint32_t> subArrEnds, uint32_t pairNum, uint32_t prevInd);
void ReadBinFile(std::string dir, std::vector<double>& data);
void WriteBinFile(std::string dir, std::vector<double>& data);
void RandomData(std::vector<double>& data);

void main(){
	
	vector<double> data = { 8, 3, 4, 2, 5, 1, 1, 0, 7, 8 };
	//RandomData(data);
	//WriteBinFile("rnd_data.bin", data);
	//ReadBinFile("rnd_data.bin", data);
	cout << "reading data" << endl;
	uint32_t count(0);
	for (double i : data) {
		cout << i << "\t";

		// Если вывели 5 чисел, то вставляем символ новой строки
		if ((count + 1) % 5 == 0)
			std::cout << "\n";
		++count;
	}

	NaturalMergeSort(data, Merge);
}

void NaturalMergeSort(std::vector<double>& data, mergeFnc Merge) {
	vector<uint32_t> subArrEnds;
	for (uint32_t i = 0; i < (data.size() -  1); ++i) {
		if (data[i] > data[i + 1]) {
			subArrEnds.push_back(i);
		}
	}
	subArrEnds.push_back(data.size() - 1);
	for (auto i : subArrEnds) {
		cout << i << " ";
	}
	cout << endl;
	Merge(data, subArrEnds, 1, 0);
}

void Merge(std::vector<double>& data, vector<uint32_t> subArrEnds, uint32_t pairNum, uint32_t prevInd) {
	
	if (subArrEnds.size() > 1 || pairNum * 2 - 1 < subArrEnds.size()) {
		uint32_t l = subArrEnds[pairNum * 2 - 2], r = subArrEnds[pairNum * 2 - 1];
		
		
		for (uint32_t couner(prevInd + 1); couner < r - prevInd; ++couner) {
			if (data[couner] > data[l + couner + 1]) {
				data[l + couner + 1] -= data[couner];
				data[couner] += data[l + couner + 1];
				data[l + couner + 1] = data[couner] - data[l + couner + 1];
			}
			else if (data[couner] = data[l + couner + 1]) {
				data.insert(data.begin() + couner, data[l + couner + 1]);
				data.erase(data.begin() + l + couner + 1);
			}
		}

		cout << "merge array: " << endl;
		for (auto i : data) {
			cout << i << " ";
		}
		cout << endl;


		Merge(data, subArrEnds, pairNum + 1, r);
		subArrEnds.erase(subArrEnds.begin() + pairNum - 1);
		Merge(data, subArrEnds, pairNum + 1, r);
	}






}

void ReadBinFile(std::string dir, std::vector<double>& data) {

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
		double val = rand() / 100.;
		data.push_back(val);
		std::cout << val << "\t";

		// Если вывели 5 чисел, то вставляем символ новой строки
		if ((count + 1) % 5 == 0)
			std::cout << "\n";
	}
}