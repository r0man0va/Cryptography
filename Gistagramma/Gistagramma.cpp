#include <iostream>
#include <fstream> // работа с файлами
#include <sstream> // дл€ потока симовлов из файла, чтоб считать и закрыть
#include <string>
#include <windows.h>
#include <vector>
#include <algorithm>

using namespace std;

struct Sequence 
{
    string sequence_string;  // изначальна€ послед считанна€ из файла
    vector<int> sequence_full;  // изначальна€ послед типа int
    vector<char> sequence_full_char; // изначал послед типа char
    vector<int> sequence_unique;  //только уникальные элем из послед
    vector<char> sequence_unique_char;  // только уникал эелем из послед типа char
    vector<int> sequence_ascii;  // уникал char элем с кодом символа ascii
};

string readFromFile(const char* fileName) { // принимает argv[] из getSequenceFromFile

    ifstream fileIn(fileName);
    string str((istreambuf_iterator<char>(fileIn)),
        istreambuf_iterator<char>());
    fileIn.close();

    return str;
}

void writeIntoFile(const char* fileName, string seq_str, vector<int> seq_full, vector<int> seq_unique, vector<int> seq_ascii) {

    ofstream outputFile;
    outputFile.open(fileName);
    if (outputFile.is_open()) {
    
        outputFile << "√»—“ќ√–јћћј –ј—ѕ–≈ƒ≈Ћ≈Ќ»я ЁЋ≈ћ≈Ќ“ќ¬" << endl;
        outputFile << endl << "¬с€ последовательность:  " << seq_str << endl;

        for (int i = 0; i < seq_unique.size(); i++) {

            outputFile << "Ёлемент " << seq_unique[i] << " в ASCII " << seq_ascii[i] << " по€влетс€ : "
                << count(seq_full.begin(), seq_full.end(), seq_unique[i]) << endl;
        }

    }
    outputFile.close();
}

vector<int> getSequenceFromFile(string seqStr) {
    // получает строку с изнача послед, избавл€етс€ от пробелов и добавл€ет только int в вектор
    vector<int> sequence;
    istringstream seqStrStream(seqStr);
    string elem;
    while (getline(seqStrStream, elem, ' ')) {
    
        sequence.push_back(stoi(elem));
    }
    return sequence;

}


vector<char> getSequenceFromFile_char(string seqStr) {
    // получает строку с изнача послед, избавл€етс€ от пробелов в строке и добавл€ет char числа в вектор
    seqStr.erase(remove(seqStr.begin(), seqStr.end(), ' '), seqStr.end());
    vector<char> sequence(seqStr.begin(), seqStr.end());
  
    return sequence;

}

vector<int> makeSeqWithUniqueElems(vector<int> vect0) { //vect0 - изначальна€ послед
    vector<int> vect;                                  //vect - нова€ послед с уникальными элем
    for (int item : vect0) {       // из числового вектора с полной последовательностью
        if (vect.empty()) {       // формирует новый int вектор, но только с уникальными эелем из послед

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

vector<char> makeSeqWithUniqueElems(vector<char> vect0) { //vect0 - изначальна€ послед
    vector<char> vect;                                  //vect - нова€ послед с уникальными элем
    for (int item : vect0) {               // из char вектора с полной последовательностью
        if (vect.empty()) {               // формирует новый char вектор, но только с уникальными эелем из послед

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

vector<int> makeUniqueASCIISeq(vector<char> vect0) {
                          // получает char с уникал элем и формирует 
    vector<int> vect;     // новый вектор int с переведенными char элем в соответств им ascii-код  
    for (char item : vect0) {
        vect.push_back((int)item);
    }

    return vect;

}

int main(int argc, char* argv[]) {// имеетс€ два txt файла: argv[1]-sequence.txt(сама последовательность 4 2 1 7)
                                 // argv[2]-gistagramma.txt (куда будет записан результат данного теста)
    setlocale(LC_ALL, ".1251");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    //1. string sequence_string;  2. vector<int> sequence_full; 3. vector<char> sequence_full_char;  4. vector<int> sequence_unique; 5. vector<int> sequence_unique_char;  6. vector<char> sequence_ascii;

    Sequence seq;
    seq.sequence_string = readFromFile(argv[1]);
    seq.sequence_full = getSequenceFromFile(seq.sequence_string);
    seq.sequence_full_char = getSequenceFromFile_char(seq.sequence_string);
    seq.sequence_unique = makeSeqWithUniqueElems(seq.sequence_full);
    seq.sequence_unique_char = makeSeqWithUniqueElems(seq.sequence_full_char);
    seq.sequence_ascii = makeUniqueASCIISeq(seq.sequence_unique_char);

    writeIntoFile(argv[2], seq.sequence_string, seq.sequence_full, seq.sequence_unique, seq.sequence_ascii);


    return 0;
}