#include <iostream>
#include <fstream> // ������ � �������
#include <sstream> // ��� ������ �������� �� �����, ���� ������� � �������
#include <string>
#include <windows.h>
#include <cstdio>
#include <math.h>
#include <bitset>

using namespace std;

uint64_t findModulus(uint64_t p, uint64_t q) {

    return p * q;
}

uint64_t EulerFunction(uint64_t p, uint64_t q) {

    return ((p - 1) * (q - 1));
}

uint64_t GCD(uint64_t e, uint64_t fi)
{ // ��� (� - ���� ����������, fi - ������� ������)
    while (e > 0)
    {
        uint64_t myTemp;
        myTemp = e;
        e = fi % e;
        fi = myTemp;
    }

    return fi;
}

uint64_t findE(uint64_t fi) // ������� � - �������� ����������
{
    // 1. ������ ���� ����� ����� e � ��������� ( 1 < e < fi ) 2. ������� ������� � fi , ��� ����� fi - ������� ������
    for (uint64_t e = 2; e < fi; e++)
    {
        if (GCD(e, fi) == 1) //�������� �� ��, ��� e � fi - �������-������� ���� � ������
        {
            return e;
        }
    }
    return -1;
}

uint64_t findD(uint64_t e, uint64_t fi)
{ // ������� ����� d �������� ����� e �� ������ fi, �.�. �����, ��������������� d * e ? 1 (mod fi)
    uint64_t d;
    uint64_t k = 1;

    while (true)
    {
        k = k + fi;

        if (k % e == 0)
        {
            d = (k / e);
            return d;
        }
    }
}

int modexp(int int_symbol, int power_number, int modulus)
{
    if (power_number == 0) return 1;
    int z = modexp(int_symbol, power_number / 2, modulus);
    if (power_number % 2 == 0)
        return (z * z) % modulus;
    else
        return (int_symbol * z * z) % modulus;
}

string crypting(string text, string& cryptedText, uint64_t power, uint64_t modulus) {
    uint64_t step1, step2, step3;
    for (byte symbol : text) {
        cout << (int)symbol;
        //step1 = pow(symbol, power);
        //step2 = step1 % modulus;
        step2 = modexp(symbol, power, modulus);
        step3 = (byte)step2;
        //byte newCh = (byte)(pow((int)symbol, power)) % modulus;
        cryptedText += step3;
        //cout << (char)(int)symbol;
    }
    return cryptedText;
}

string readFrom(char* filePath) {
    string file;
    ifstream file0(filePath);
    if (!file0.is_open()) {
        exit(-1);
    }

    getline(file0, file);
    file0.close();

    return file;
}

int main(int argc, char* argv[]) {

    setlocale(LC_ALL, ".1251");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string binary = bitset<8>(65).to_string(); //to binary
    string binary1 = bitset<8>(66).to_string(); //to binary

    cout << (int)"A" << endl;
    cout << (int)"B" << endl;
    cout << stoi(binary) << "\n";
    cout << stoi(binary1) << "\n";
    string binary12;
    binary12 += binary;
    binary12 += binary1;
    cout << "bin12 = " << binary12 << endl;
    //cout << "stoi bin12 = " << stoi(binary12) << endl;


    unsigned long decimal = bitset<8>(binary).to_ulong();
    unsigned long decimal12 = bitset<16>(binary12).to_ulong();

    cout << decimal << "\n";
    cout << "bin12 decimal = " << decimal12 << endl;
    cout << "3377 ^ 17143 mod 24341 = " << modexp(3377, 17143, 24341) << endl;

    string decrypted_C;
    string crypted_C;
    string C_toCrypt = readFrom(argv[1]);
    uint64_t p, q, modulus, fi, e, d;
    cout << "RSA ����������" << endl << "��� 1. ���������� ������." << endl;
    p = stoi(readFrom(argv[2]));
    q = stoi(readFrom(argv[3]));
    cout << "p = " << p << " , q = " << q << endl;

    modulus = findModulus(p, q);
    cout << "��� 2. ������ p * q = " << modulus;

    fi = EulerFunction(p, q);
    cout << endl << "��� 3. ������� ������� ������. � = " << fi;

    e = findE(fi);
    cout << endl << "��� 4. ������� ����� � - �������� ����������. e = " << e;

    cout << endl << "�������� ���� {e , modulus} = " << "{" << e << " , " << modulus << "}";

    d = findD(e, fi);
    cout << endl << "��� 5. ������� ����� d - ����� �������� e � �� ������ fi. d = e^(-1) mod fi = " << d;

    cout << endl << "��������� ���� {d , modulus} = " << "{" << d << " , " << modulus << "}";

    cout << endl << "�������� �����." << endl << C_toCrypt << endl;

    crypted_C = crypting(C_toCrypt, crypted_C, e, modulus);
    cout << endl << "������������� �����." << endl << crypted_C;
    ofstream crypted_C_0(argv[4]);
    crypted_C_0 << (crypted_C);
    crypted_C_0.close();

    decrypted_C = crypting(crypted_C, decrypted_C, d, modulus);
    cout << endl << "������������ �������������� ������." << endl << decrypted_C << endl;
    ofstream decrypted_C_0(argv[5]);
    decrypted_C_0 << (decrypted_C);
    decrypted_C_0.close();

    return 0;
}