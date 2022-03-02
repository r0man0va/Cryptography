#include <iostream>
#include <fstream> // работа с файлами
#include <sstream> // для потока симовлов из файла, чтоб считать и закрыть
#include <string>
#include <map>
#include <windows.h>
#include <vector>
#include <algorithm>
#include <bitset>
#include <boost/dynamic_bitset.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


using namespace std;

struct Correlation {
	string sequence;
	vector<int> RnVector;
	float R;
	float MF;
};

int sum_of_digit(int n, int val)
{
	if (n < 10)
	{
		val = val + n;
		return val;
	}
	return sum_of_digit(n / 10, (n % 10) + val);
}



vector<int> bitsetXOR(string seq) {
	int seqLen = seq.length(); //длина послед, чтобы уменьшать потом bitset
	int seqInt = stoi(seq, 0, 2); //
	string D, DA,DB, DC;
	int sumOfDigits, r; 
	int shift = 0;
	vector<int> rVector;
	
	for (int i = seqLen; i > 0; i--) {
	// C = A ^ B
		boost::dynamic_bitset<> A(i, seqInt);
		boost::to_string(A, DA);
		boost::dynamic_bitset<> B(i, seqInt >> shift);
		boost::to_string(B, DB);
		boost::dynamic_bitset<> C(i);
		
		
		C.operator=(A);
		boost::to_string(C, D);
		C.operator^=(B);
		boost::to_string(C, D); // D - строка битсета "110110"
		sumOfDigits = sum_of_digit(stoi(D.c_str()), 0); // сумма всех цифр; в строке "110110" = 4
		// r = seqLen - сдвиг - (2 * сумма)
		r = seqLen - shift - 2 * sumOfDigits;
		rVector.push_back(r);
		shift++;
		
	}

	return rVector;
}

float findR(vector<int> rVec) {
	float R;
	int rVecSize = rVec.size();
	int r;
	if (rVec[1] != 0) {
	
		r = rVec[1];
	}
	else {
		for (int i = 1; i < rVec.size(); i++) {
		
			if (rVec[i] != 0) {
			
				r = rVec[i];
			}
		}
	}
	R = rVecSize/abs(r);

	return R;
}

float findMF(vector<int> rVec) {
	float MF;
	int rVecSize = rVec.size();
	int summOfPowerRn = 0;
	for (int i = 0; i < rVecSize; i++) {
	
		summOfPowerRn += pow(rVec[i], 2);
	}
	MF = rVecSize / sqrt(summOfPowerRn);

	return MF;
}

void printOutResults(Correlation seq) {

	cout << "КОРЕЛЯЦИОННЫЙ КРИТЕРИЙ" << endl;
	cout << "Последовательность: " << seq.sequence << endl;
	cout << "r = { ";
	for (auto& elem : seq.RnVector) {
	
		cout << elem << " ";
	}
	cout << "}" << endl;
	cout << "R = " << seq.R << endl;
	cout << "MF = " << seq.MF << endl;

}

int main() {

	setlocale(LC_ALL, ".1251");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Correlation seq;
	seq.sequence = "110110";
	seq.RnVector = bitsetXOR(seq.sequence);
	seq.R = findR(seq.RnVector);
	seq.MF = findMF(seq.RnVector);
	printOutResults(seq);


	return 0;
}