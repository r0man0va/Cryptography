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
    multimap <string, int> MP;
    
};

string readFromFile(const char* fileName) { // ��������� argv[] �� getSequenceFromFile

    ifstream fileIn(fileName);
    string str((istreambuf_iterator<char>(fileIn)),
        istreambuf_iterator<char>());
    fileIn.close();

    return str;
}

vector<int> vecSequence(string seqStr) {

    vector<int> sequence;
    istringstream seqStrStream(seqStr);
    string elem;
    while (getline(seqStrStream, elem, ' ')) {
    
        sequence.push_back(stoi(elem));
    }
    return sequence;
}

void printOutSeqVec(vector<int> vecSeq) {

    for (auto it = vecSeq.begin(); it != vecSeq.end(); it++) {
    
        cout << *it << " ";
    }
}

pair<int, int> decreasing(vector<int> monotonic, int position) {
    pair <int, int> pD;
    int current;
    int lenDown = 0;
    for (int i = position; i < monotonic.size(); i++) {
        if (monotonic[i] < monotonic[i - 1]) {
            lenDown += 1;
            if (i == monotonic.size() - 1) {
            
                current = i;
                pD.first = lenDown;
                pD.second = current;
                return pD;
            }
        }
        else {
            current = i;
            pD.first = lenDown;
            pD.second = current;
            return pD;
        }
    }
}

pair<int, int> increasing(vector<int> monotonic, int position) {
    pair <int, int> pI;
    int current;
    int lenUp = 0;
    for (int i = position; i < monotonic.size(); i++) {
        if (monotonic[i] > monotonic[i - 1]) {
            lenUp += 1;
            if (i == monotonic.size() - 1) {
            
                current = i;
                pI.first = lenUp;
                pI.second = current;
                return pI;
            }
        }
        else {
            
        }

    }
}

multimap <string, int> monotonicCheck(multimap <string, int> mp, vector<int> const& monotonic, int previous, int current) {
    //map <string, int> mp;
    pair <int, int> pInc;
    pair <int, int> pDec;
    //int lenDown;
    //int lenUp;
    int newStart;
    int equalStart = 0;
    
    if (current == monotonic.size() - 1) { // ������� ������
    
        return mp;
    }
    /*if (monotonic[current] == monotonic[previous]) {
        monotonicCheck(mp, monotonic, current, current+1);
        equalStart += 1;

    }*/

    if (monotonic[current] < monotonic[previous]) {
        pDec = decreasing(monotonic, current);// ������ pair<����� ������� , ����� �����>
        newStart = pDec.second;
        previous = newStart-1;
        //mp["���������"] = pDec.first;
        mp.insert(make_pair("��������", pDec.first));
        monotonicCheck(mp, monotonic,previous, newStart);
        
    }
    if(monotonic[current] > monotonic[previous]) {
        pInc = increasing(monotonic, current);// ���������� ����
        newStart = pInc.second;
        previous = newStart-1;
        //mp["������������"] = pInc.first;
        mp.insert(make_pair("�����������", pInc.first));
        monotonicCheck(mp, monotonic, previous, newStart);

    }
    //mp.begin()->second += equalStart;
    return mp;
}

int main(int argc, const char* argv[]) {

    setlocale(LC_ALL, ".1251");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Sequence seq;
    seq.sequence_full_string = readFromFile(argv[1]);
    seq.sequence_full_int = vecSequence(seq.sequence_full_string);

    cout << "�������� �� ������������" << endl;
    cout << "��� ������������������ : " << endl;
    printOutSeqVec(seq.sequence_full_int);
    cout << endl;
    multimap <string, int> M;
   /* M = monotonicCheck(seq.MP, seq.sequence_full_int, 0, 1);
    M.rbegin()->second += 1; // ��� ����� ����� 0, �� ��-�� ������� ��� 1-�� ���� map ����� +1
    for (auto it=M.rbegin(); it != M.rend(); ++it) {
    
        cout << "������� "<<it->first << " ������ " << it->second << endl;
    }*/

    //M["������ "] = 1;
    M.insert(make_pair("������ ", 2));
    M.insert(make_pair("������ ", 2));
    M.insert(make_pair("������ ", 3));

    //M.rbegin()->second += 1; // ��� ����� ����� 0, �� ��-�� ������� ��� 1-�� ���� map ����� +1
    for (auto it = M.begin(); it != M.end(); ++it) {

        cout << "������� " << it->first << " ������ " << it->second << endl;
    }
    

    //������ ������.1. ��������� 0 � 1 ����. ��� ������ ��� �������. � ����� ��� ��������� � �� ������� ��� �������� ����� �������, ���� �� �� ������ ���
    //2. ��� ������ ������� ��� �� ����� ��������� �� ���������� ���� ���� ��� ������. ��� ������� ��������� ������ ��������� ������� ����� �������.
    // ������ ������� �������� �� ��� ���� ����� 0 � 1 �������

    return 0;
}