#include <iostream>
#include <fstream> // ������ � �������
#include <sstream> // ��� ������ �������� �� �����, ���� ������� � �������
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

string readFromFile(const char* fileName) { // ��������� argv[] �� getSequenceFromFile

    ifstream fileIn(fileName);
    string str((istreambuf_iterator<char>(fileIn)),
        istreambuf_iterator<char>());
    fileIn.close();

    return str;
}

vector<int> getIntSequenceFromStr(string seqStr) {
    // �������� ������ � ������ ������, ����������� �� �������� � ��������� ������ int � ������
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

        outputFile << "�������� �����" << endl;
        outputFile << endl << "��� ������������������:  " << bitSeqStr << endl;

        outputFile << "������� 0 � 1: " << endl;
        outputFile << "����� 0 ��������� : "
                << count(bitSeqStr.begin(), bitSeqStr.end(), '0') << endl;
        outputFile << "����� 1 ��������� : "
                << count(bitSeqStr.begin(), bitSeqStr.end(), '1') << endl;
    
    }
    outputFile.close();
}

void seriesByTwo(string bit_seq_str) {

    map<string, int> counter2;

    cout << endl << "����� �����-���: ";
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
        cout << "�����: " << item.first << " ��������� " << item.second << " ����" << endl;
    }
}

void seriesByThree(string bit_seq_str) {

   map<string, int> counter3;
   cout << endl << "����� �����-�����: ";
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
       cout << "�����: " << item.first << " ��������� " << item.second << " ����" << endl;
    }

}

void seriesByFour(string bit_seq_str) {

    map<string, int> counter4;

    cout << endl << "����� �����-��������: ";
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
        cout << "�����: " << item.first << " ��������� " << item.second << " ����" << endl;
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

    cout << "�������� �����" << endl;
    cout << "��� ������������������ : ";
    for (auto it = seq.sequence_full_int.begin(); it != seq.sequence_full_int.end(); it++)
    {
        cout << *it << ' ';
    }
    cout << endl;
    cout << "� ������� ���� : " << endl;
    for (auto it = seq.sequence_full_bitset.begin(); it != seq.sequence_full_bitset.end(); it++)
    {
        cout << *it << ' ';
    }
    cout << endl;


    countingOnesZeros(argv[2], seq.bit_sequence_string); // ������� 0 � 1
    seriesByTwo(seq.bit_sequence_string); // ������� �����-���
    seriesByThree(seq.bit_sequence_string); // ������� �����-�����
    seriesByFour(seq.bit_sequence_string); // ������� �����-��������

    return 0;
}