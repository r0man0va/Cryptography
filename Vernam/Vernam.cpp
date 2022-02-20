
#include <iostream>
#include <fstream> // работа с файлами
#include <sstream> // для потока симовлов из файла, чтоб считать и закрыть
#include <string>
#include <windows.h>

using namespace std;

string readFrom(char * filePath) {
    string file;
    ifstream file0(filePath);
    if (!file0.is_open()) {
        exit(-1);
    }

    getline(file0, file);
    file0.close();
    
    return file;
}

string crypting(string codeF, string keyF, string encryptedF) {// что шифровать, ключ, куда записывать
    for (int i = 0; i < codeF.length(); i++) {
        encryptedF += codeF[i] ^ keyF[i];
    }
    return encryptedF;
}

int main(int argc, char * argv[])
{
    setlocale(LC_ALL, ".1251");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string fileToCode = readFrom(argv[1]); //работа с файлом исход текста code.txt
    string keyFile = readFrom(argv[2]); // работа с файлом ключа key.txt

    string encryptedFile;// работа с файлом для зашифров текста encrypted.txt 
    ofstream encryptedFile0(argv[3]);
    //шифрование
    encryptedFile = crypting(fileToCode, keyFile, encryptedFile);    
    string encryptedFileCOPY = encryptedFile;
    encryptedFile0 << encryptedFile;
    encryptedFile0.close();
    //cout << encryptedFileCOPY << endl;

    //дешифрование
    string decryptedFile; // работа с файлом для расшифров текста decrypted.txt
    ofstream decryptedFile0(argv[4]);
    decryptedFile0 << crypting(encryptedFileCOPY, keyFile, decryptedFile);
    decryptedFile0.close();

       
    return 0;
}
