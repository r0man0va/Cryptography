#include <iostream>
#include <fstream> // работа с файлами
#include <sstream> // для потока симовлов из файла, чтоб считать и закрыть
#include <string>
#include <windows.h>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

string readFromFile(const char* fileName) { // принимает argv[] из getSequenceFromFile

    ifstream fileIn(fileName);
    string str((istreambuf_iterator<char>(fileIn)),
        istreambuf_iterator<char>());
    fileIn.close();

    return str;
}

vector<int> getSequenceFromFile(const char* fileName) {

    vector<int> sequence;
    string seqStr = readFromFile(fileName);
    istringstream seqStrStream(seqStr);
    string elem;
    while (getline(seqStrStream, elem, ' ')) {
    
        sequence.push_back(stoi(elem));
    }
    return sequence;

}

vector<int> makeSeqWithUniqueElems(vector<int> vect0) { //vect0 - изначальная послед
    vector<int> vect;                                  //vect - новая послед с уникальными элем
    for (int item : vect0) {
        if (vect.empty()) {

            vect.push_back(item);
        }
        else {

            if (!(find(vect.begin(), vect.end(), item) != vect.end())) {

                vect.push_back(item);
            }
        }
    }
    return vect;
}

void countUniqueElemsInSeq(vector<int> vect0, vector<int> vect) {

    for (int item : vect) {
        cout << "Элемент " << item << " появляется : "
            << count(vect0.begin(), vect0.end(), item) << endl;
    }

}

int main(int argc, char * argv[]) {

    setlocale(LC_ALL, ".1251");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    vector<int> Sequence = getSequenceFromFile(argv[1]);
    vector<int> Sequence_unique = makeSeqWithUniqueElems(Sequence);
    countUniqueElemsInSeq(Sequence, Sequence_unique);

    cout << endl << "Вектор" << endl;
    for (auto it = begin(Sequence); it != end(Sequence); ++it) {
        cout<< *it << " ";
    }

   
    cout << endl<< (int)'3' << endl;


    return 0;
}