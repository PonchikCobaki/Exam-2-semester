#include <iostream>
#include <list>
#include <iterator>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

using mergeFnc = uint16_t(*)(std::vector<double>& data, vector<uint32_t>& subArrEnds, uint32_t pairNum, int64_t prevInd);

void NaturalMergeSort(std::vector<double>& data, mergeFnc Merge);
uint16_t Merge(std::vector<double>& data, vector<uint32_t>& subArrEnds, uint32_t pairNum, int64_t prevInd);
void ReadBinFile(std::string dir, std::vector<double>& data);
void WriteBinFile(std::string dir, std::vector<double>& data);
void RandomData(std::vector<double>& data);

void main(){
	
	//vector<double> data = { 8, 3, 4, 2, 5, 1, 1, 0, 7, 8, 55 };
	vector<double> data = { 223.6,   49.78,   320.41,  155.2,   174.89, 264.16,  276.97 };
	//vector<double> data;
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
	for (uint32_t i = 0; i < (data.size() -  1); ++i) {
		if (data[i] > data[i + 1]) {
			subArrEnds.push_back(i);
		}
	}
	subArrEnds.push_back(data.size() - 1);	// последний подмассив
	for (auto i : subArrEnds) {
		cout << i << " ";
	}
	cout << endl;
	Merge(data, subArrEnds, 1, -1);
}

uint16_t Merge(std::vector<double>& data, vector<uint32_t>& subArrEnds, uint32_t pairNum, int64_t prevInd) {

	if (subArrEnds.size() > 1 && (pairNum * 2 <= subArrEnds.size() && subArrEnds.size() / 2 != 0)) {
		int64_t l = subArrEnds[pairNum * 2 - 2], r = subArrEnds[pairNum * 2 - 1];	// левый и правый индексы концов подмассивов
		int64_t lLen = int64_t(l) - prevInd, rLen = r - l;	// длинна левого и правого подмассива
		int64_t i(0), j(0);
		for (uint32_t counter(prevInd + 1); counter < r; ++counter) {
			if (lLen == rLen && lLen + counter - i > r) {
				break;
			}
			else if ((lLen > rLen && counter > l)) {
				break;
			}
			else if (lLen < rLen && counter == r) {
				break;
			}

			if (counter > l && lLen > 1) {
				counter += lLen - 1;
			}
			if (int64_t(lLen) + int64_t(counter) - i - 1 >= r) {
				i += lLen + counter - i - r;
			}

			if (data[counter] > data[lLen + counter - i]) {
				data[lLen + counter - i] -= data[counter];
				data[counter] += data[lLen + counter - i];
				data[lLen + counter - i] = data[counter] - data[lLen + counter - i];
			}
			else if (data[counter] == data[lLen + counter - i] && (counter + 1) != (lLen + counter - i)) {
				if (data[lLen + counter - i - 1] > data[lLen + counter - i]) {
					data.insert(data.begin() + counter, data[lLen + counter - i]);
					data.erase(data.begin() + (lLen + counter - i));
				}
				else if (data[lLen + counter - i - 1] < data[lLen + counter - i]) {
					data.insert(data.begin() + (lLen + counter - i), data[counter]);
					data.erase(data.begin() + counter);
				}
			}
			else if (data[counter] < data[lLen + counter - i] && (counter + 1) != (lLen + counter - i)) {
					++i;
				}
		}

		cout << "merge array: " << endl;
		for (auto i : data) {
			cout << i << " ";
		}
		cout << endl;

		uint16_t flag(false);
		while (subArrEnds.size() > 1) {
			flag = Merge(data, subArrEnds, pairNum + 1, r);
			if (subArrEnds.size() > 1) {
				subArrEnds.erase(subArrEnds.begin() + pairNum * 2 - 2);
			}
			if (flag){
				flag = false;
				if (pairNum != 1) {
					return 1;
				}
				pairNum = 0;
				r = -1;
				
			}
		}
	}

	return 1;

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