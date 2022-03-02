#include <iostream>
#include <fstream> // ������ � �������
#include <sstream> // ��� ������ �������� �� �����, ���� ������� � �������
#include <string>
#include <windows.h>
#include <vector>
#include <algorithm>

using namespace std;

struct Sequence 
{
    string sequence_string;  // ����������� ������ ��������� �� �����
    vector<int> sequence_full;  // ����������� ������ ���� int
    vector<char> sequence_full_char; // ������� ������ ���� char
    vector<int> sequence_unique;  //������ ���������� ���� �� ������
    vector<char> sequence_unique_char;  // ������ ������ ����� �� ������ ���� char
    vector<int> sequence_ascii;  // ������ char ���� � ����� ������� ascii
};

string readFromFile(const char* fileName) { // ��������� argv[] �� getSequenceFromFile

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
    
        outputFile << "����������� ������������� ���������" << endl;
        outputFile << endl << "��� ������������������:  " << seq_str << endl;

        for (int i = 0; i < seq_unique.size(); i++) {

            outputFile << "������� " << seq_unique[i] << " � ASCII " << seq_ascii[i] << " ��������� : "
                << count(seq_full.begin(), seq_full.end(), seq_unique[i]) << endl;
        }

    }
    outputFile.close();
}

vector<int> getSequenceFromFile(string seqStr) {
    // �������� ������ � ������ ������, ����������� �� �������� � ��������� ������ int � ������
    vector<int> sequence;
    istringstream seqStrStream(seqStr);
    string elem;
    while (getline(seqStrStream, elem, ' ')) {
    
        sequence.push_back(stoi(elem));
    }
    return sequence;

}


vector<char> getSequenceFromFile_char(string seqStr) {
    // �������� ������ � ������ ������, ����������� �� �������� � ������ � ��������� char ����� � ������
    seqStr.erase(remove(seqStr.begin(), seqStr.end(), ' '), seqStr.end());
    vector<char> sequence(seqStr.begin(), seqStr.end());
  
    return sequence;

}

vector<int> makeSeqWithUniqueElems(vector<int> vect0) { //vect0 - ����������� ������
    vector<int> vect;                                  //vect - ����� ������ � ����������� ����
    for (int item : vect0) {       // �� ��������� ������� � ������ �������������������
        if (vect.empty()) {       // ��������� ����� int ������, �� ������ � ����������� ����� �� ������

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

vector<char> makeSeqWithUniqueElems(vector<char> vect0) { //vect0 - ����������� ������
    vector<char> vect;                                  //vect - ����� ������ � ����������� ����
    for (int item : vect0) {               // �� char ������� � ������ �������������������
        if (vect.empty()) {               // ��������� ����� char ������, �� ������ � ����������� ����� �� ������

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
                          // �������� char � ������ ���� � ��������� 
    vector<int> vect;     // ����� ������ int � ������������� char ���� � ���������� �� ascii-���  
    for (char item : vect0) {
        vect.push_back((int)item);
    }

    return vect;

}

int main(int argc, char* argv[]) {// ������� ��� txt �����: argv[1]-sequence.txt(���� ������������������ 4 2 1 7)
                                 // argv[2]-gistagramma.txt (���� ����� ������� ��������� ������� �����)
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