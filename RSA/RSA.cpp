#include <iostream>
#include <fstream> // ������ � �������
#include <sstream> // ��� ������ �������� �� �����, ���� ������� � �������
#include <string>
#include <windows.h>
#include <cstdio>
#include <vector>

using namespace std;
using ArrayInt = vector<uint64_t>;

uint64_t findModulus(uint64_t const& p, uint64_t const& q) {

    return p * q;
}
uint64_t EulerFunction(uint64_t const& p, uint64_t const& q) {

    return ((p - 1) * (q - 1));
}
uint64_t GCD(uint64_t  e, uint64_t  fi)
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
uint64_t findE(uint64_t const& fi) // ������� � - �������� ����������
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
uint64_t findD(uint64_t const& e, uint64_t const& fi)
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
uint64_t modexp(uint64_t const& int_symbol, uint64_t const& power_number, uint64_t const& modulus)
{
    if (power_number == 0) return 1;
    uint64_t z = modexp(int_symbol, power_number / 2, modulus);
    if (power_number % 2 == 0)
        return (z * z) % modulus;
    else
        return (int_symbol * z * z) % modulus;
}

unsigned short byteUnion(unsigned char byte1, unsigned char byte2)
{
    return byte1 << 8 | byte2;
}

ArrayInt encryptingByByte(string const& text, uint64_t const& power, uint64_t const& modulus)
{
    ArrayInt result;
    uint64_t encryptChar;
    for (byte symbol : text)
    {
        encryptChar = modexp(symbol, power, modulus);
        result.push_back(encryptChar);
    }
    return result;
}
ArrayInt decryptingByByte(ArrayInt const& text, uint64_t const& power, uint64_t const& modulus)
{
    ArrayInt result;
    uint64_t decryptChar;
    for (uint64_t encryptChar : text)
    {
        decryptChar = modexp(encryptChar, power, modulus);
        result.push_back(decryptChar);
    }
    return result;
}

ArrayInt encryptingByWord(string const& text, uint64_t const& power, uint64_t const& modulus)
{
    ArrayInt result;
    unsigned char nextByte;

    for (int i = 0; i < text.size(); i += 2)
    {
        if (((text.size() % 2 != 0) and (text[i] == text.back())))
        {
            nextByte = 0;
        }
        else
        {
            nextByte = text[i + 1];
        }
        result.push_back(modexp(byteUnion(text[i], nextByte), power, modulus));
    }
    return result;
}
ArrayInt decryptingByWord(ArrayInt const& text, uint64_t const& power, uint64_t const& modulus)
{
    ArrayInt result;
    uint64_t decryptBytes;

    for (uint64_t word : text)
    {
        decryptBytes = modexp(word, power, modulus);
        result.push_back(decryptBytes >> 8);
        result.push_back((unsigned char)decryptBytes);
    }
    return result;
}

string readFrom(char* filePath)
{
    string file;
    ifstream file0(filePath);
    if (!file0.is_open()) {
        exit(-1);
    }

    getline(file0, file);
    file0.close();

    return file;
}

void writeToFile(const char* file, ArrayInt text)
{
    ofstream encryptedTextFile(file);
    for (uint64_t elem : text)
    {
        encryptedTextFile << (unsigned char)elem;
    }
    encryptedTextFile.close();
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, ".1251");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string textToCrypt = readFrom(argv[1]);
    uint64_t p, q, modulus, fi, e, d;

    cout << "RSA ����������" << endl;

    cout << "��� 1. ���������� ������.";
    p = stoi(readFrom(argv[2]));
    q = stoi(readFrom(argv[3]));
    cout << " p = " << p << " , q = " << q << endl;

    modulus = findModulus(p, q);
    cout << "��� 2. ������ p * q = " << modulus << endl;

    fi = EulerFunction(p, q);
    cout << "��� 3. ������� ������� ������. � = " << fi << endl;

    e = findE(fi);
    cout << "��� 4. ������� ����� � - �������� ����������. e = " << e << endl;
    d = findD(e, fi);
    cout << "��� 5. ������� ����� d - ����� �������� e � �� ������ fi. d = e^(-1) mod fi = " << d << endl;

    cout << "�������� ���� {e , modulus} = " << "{" << e << " , " << modulus << "}" << endl;
    cout << "��������� ���� {d , modulus} = " << "{" << d << " , " << modulus << "}" << endl;

    //cout << "�������� �����." << endl << textToCrypt << endl;

    ArrayInt encryptedText;
    ArrayInt decryptedText;

    if (modulus < 255)
    {
        cout << "��� ������ ������ 255, ����� ��������� �� 1 �����, ��������� p*q > 255\n��� ���������� �� 2 �����, ���������� p*q > 65535." << endl;
        exit(1);
    }

    if (modulus > 255 and modulus < 65535)
    {
        cout << "��� ������ ������ 65535, �� ������ ��� 255, ������� ������� 1 ������. " << endl;

        encryptedText = encryptingByByte(textToCrypt, e, modulus);
        writeToFile(argv[4], encryptedText);

        decryptedText = decryptingByByte(encryptedText, d, modulus);
        writeToFile(argv[5], decryptedText);
    }

    if (modulus > 65535)
    {
        cout << "��� ������ ������ 65535, �������� �� 2 �����. " << endl;

        encryptedText = encryptingByWord(textToCrypt, e, modulus);
        writeToFile(argv[4], encryptedText);

        decryptedText = decryptingByWord(encryptedText, d, modulus);
        writeToFile(argv[5], decryptedText);
    }

    return 0;
}