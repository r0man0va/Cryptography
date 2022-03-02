#include <iostream>
#include <fstream> // работа с файлами
#include <sstream> // для потока симовлов из файла, чтоб считать и закрыть
#include <string>
#include <map>
#include <windows.h>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;

struct Sequence
{
    string sequence_full_string;
    vector<int> sequence_full_int;
    vector<string> sequence_full_bitset;
    string bit_sequence_string;
};

string readFromFile(const char* fileName) { // принимает argv[] из getSequenceFromFile

    ifstream fileIn(fileName);
    string str((istreambuf_iterator<char>(fileIn)),
        istreambuf_iterator<char>());
    fileIn.close();

    return str;
}

vector<int> getIntSequenceFromStr(string seqStr) {
    // получает строку с изнача послед, избавляется от пробелов и добавляет только int в вектор
    vector<int> sequence;
    istringstream seqStrStream(seqStr);
    string elem;
    while (getline(seqStrStream, elem, ' ')) {

        sequence.push_back(stoi(elem));
    }
    return sequence;

}

vector<string> makeVecSeqInBits(vector<int> seqVecInt) {

    string str;
    vector<string> vect;
    for (char elem : seqVecInt) {
        
        str = bitset<4>(elem).to_string();
        vect.push_back(str);
    }

    return vect;
}

string makeBitSeqString(vector<string> bitSeqStr) {

    string bitStr;
    for (auto it = bitSeqStr.begin(); it != bitSeqStr.end(); it++)
    {
        bitStr += *it;
    }

    return bitStr;
}

void countingOnesZeros(const char* fileName, string bitSeqStr) {

    ofstream outputFile;
    outputFile.open(fileName);
    if (outputFile.is_open()) {

        outputFile << "Проверка серий" << endl;
        outputFile << endl << "Вся последовательность:  " << bitSeqStr << endl;

        outputFile << "Подсчет 0 и 1: " << endl;
        outputFile << "Число 0 появлется : "
                << count(bitSeqStr.begin(), bitSeqStr.end(), '0') << endl;
        outputFile << "Число 1 появлется : "
                << count(bitSeqStr.begin(), bitSeqStr.end(), '1') << endl;
    
    }
    outputFile.close();
}

void seriesByTwo(string bit_seq_str) {

    map<string, int> counter2;

    cout << endl << "Число серий-пар: ";
    for (int i = 0; i != bit_seq_str.size(); i += 2) {
        string s1 = bit_seq_str.substr(i, 2);
        cout << s1 << " ";
    }
    cout << endl;
    for (int i = 0; i != bit_seq_str.size(); i += 2)
    {
        string s1 = bit_seq_str.substr(i, 2);
        counter2[s1] += 1;
    }
    for (auto& item : counter2)
    {
        cout << "Серия: " << item.first << " появлется " << item.second << " раза" << endl;
    }
}

void seriesByThree(string bit_seq_str) {

   map<string, int> counter3;
   cout << endl << "Число серий-троек: ";
   for (int i = 0; i != bit_seq_str.size(); i += 3) {
       string s1 = bit_seq_str.substr(i, 3);
       if (s1.length() == 3) {
       
            cout << s1 << " ";
            continue;
       }
       break;
       
   };
   if (bit_seq_str.size() % 3 != 0) 
   { 
       cout << bit_seq_str.substr(bit_seq_str.size() - bit_seq_str.size() % 3, bit_seq_str.back()); 
   }
   cout << endl;
   for (int i = 0; i != bit_seq_str.size(); i += 3)
    {
       string s1 = bit_seq_str.substr(i, 3);
       if (s1.length() == 3) {
        
           counter3[s1] += 1;
           continue;
        }
       break;
        
    }
   for (auto& item : counter3)
   {
       cout << "Серия: " << item.first << " появлется " << item.second << " раза" << endl;
    }

}

void seriesByFour(string bit_seq_str) {

    map<string, int> counter4;

    cout << endl << "Число серий-четверок: ";
    for (int i = 0; i != bit_seq_str.size(); i += 4) {
        string s1 = bit_seq_str.substr(i, 4);
        cout << s1 << " ";
    }
    cout << endl;
    for (int i = 0; i != bit_seq_str.size(); i += 4)
    {
        string s1 = bit_seq_str.substr(i, 4);
        counter4[s1] += 1;
    }
    for (auto& item : counter4)
    {
        cout << "Серия: " << item.first << " появлется " << item.second << " раза" << endl;
    }
}



int main(int argc, char* argv[]) {

    setlocale(LC_ALL, ".1251");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Sequence seq;
    seq.sequence_full_string = readFromFile(argv[1]);
    seq.sequence_full_int = getIntSequenceFromStr(seq.sequence_full_string);
    seq.sequence_full_bitset = makeVecSeqInBits(seq.sequence_full_int);
    seq.bit_sequence_string = makeBitSeqString(seq.sequence_full_bitset);

    cout << "ПРОВЕРКА СЕРИЙ" << endl;
    cout << "Вся последовательность : ";
    for (auto it = seq.sequence_full_int.begin(); it != seq.sequence_full_int.end(); it++)
    {
        cout << *it << ' ';
    }
    cout << endl;
    cout << "В битовой виде : " << endl;
    for (auto it = seq.sequence_full_bitset.begin(); it != seq.sequence_full_bitset.end(); it++)
    {
        cout << *it << ' ';
    }
    cout << endl;


    countingOnesZeros(argv[2], seq.bit_sequence_string); // подсчет 0 и 1
    seriesByTwo(seq.bit_sequence_string); // подсчет серий-пар
    seriesByThree(seq.bit_sequence_string); // подсчет серий-троек
    seriesByFour(seq.bit_sequence_string); // подсчет серий-четверок

    return 0;
}