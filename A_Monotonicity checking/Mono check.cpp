#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <windows.h>

using namespace std;

struct Area
{
    string upOrDown;
    int areaLen;
};

vector<Area> monotonicityCheck(vector<int> seq, Area monoArea) {

    vector<Area> res;
    for (int i = 0; i != seq.size();)
    {
        if (seq[i + 1] == seq[i])
        {
            i += 1;
            monoArea.areaLen += 1;
            continue;
        }
        else
        {
            monoArea.areaLen += 1;
        }
        monoArea.upOrDown = (seq[i + 1] > seq[i]) ? "возрастания" : "убывания";
        int j = 1;
        if (monoArea.upOrDown == "возрастания")
        {
            while (((i + j + 1) != seq.size()) and (seq[i + j + 1] >= seq[i + j]))
            {
                monoArea.areaLen += 1;
                j += 1;
            }
            i += (j + 1);
            monoArea.areaLen++;
            res.push_back(monoArea);
            monoArea = {};
        }
        else
        {
            while (((i + j + 1) != seq.size()) and (seq[i + j + 1] <= seq[i + j]))
            {
                monoArea.areaLen += 1;
                j += 1;
            }
            i += (j + 1);
            monoArea.areaLen++;
            res.push_back(monoArea);
            monoArea = {};
        }
    }
    return res;
}

void printoutResult(vector<Area> res) {
    for (auto item : res)
        {
            cout << "Участок "<<item.upOrDown << " длиной  " << item.areaLen << endl;
        }
}

void printoutSeq(vector<int> res) {
    cout << "Последовательность: " << endl;
    for (auto item : res)
    {
        cout << item << " ";
    }
    cout << endl;
}

int main()
{
    setlocale(LC_ALL, ".1251");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    vector<int> Seq = { 1,1,1,2,3,4,5,5,5,4,4,3,2,2,2,1,2,3,4,5 };
    vector<Area> result;
    Area monotonicArea = {};

    cout << "ПРОВЕРКА НА МОНОТОННОСТЬ" << endl;

    printoutSeq(Seq);
    result = monotonicityCheck(Seq, monotonicArea);
    printoutResult(result);
   

    return 0;
}
