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

const short max_N = 100;



void linear_complexity_profile(string key)
{
	short s[max_N], c[max_N], b[max_N], t[max_N], buf[max_N], l, m, d;
	short N = key.size();
	//s-последоватлеьность[]
	cout << endl;
	cout << "Профиль линейной сложности" << endl;

	//запись входной двоичной строки в массив
	for (short i = 0; i < N; i++)
	{
		if (key[i] == '1')
			s[i] = 1;
		else
			s[i] = 0;
	}

	for (short i = 0; i <= N; i++) // заполнение массивов нулями
	{
		b[i] = 0;
		c[i] = 0;
		t[i] = 0;
	}
	b[0] = c[0] = 1;
	l = 0;
	m = -1;

	for (short n = 0; n < N; n++) //n - индкс эелемента в послед
	{
		d = s[n];  // конкретный эелемента по индексу n из послед s
		for (short i = 1; i <= l; i++)
			d += (c[i] * s[n - i]);
		d = d % 2;

		for (short i = 0; i < N; i++) // обнуление буферного массива
			buf[i] = 0;

		if (d == 1)
		{
			for (short i = 0; i <= l; i++) // T(D) = C(D)
				t[i] = c[i];

			for (short i = 0; i <= n - m; i++) // B(D)* D ^ (N - m)
				buf[i + n - m] = b[i];

			for (short i = 0; i < N; i++) //C(D) = C(D) + B(D) * D ^ (N - m)
				c[i] = (c[i] + buf[i]) % 2;

			if (l <= n / 2)
			{
				l = n + 1 - l;
				m = n;
				for (short i = 0; i <= l; i++) // B(D) = T(D)
					b[i] = t[i];
			}
		}
		cout << "L= " << l << "\t Sn: ";
		for (short i = 0; i <= n; i++)
		{
			cout << s[i];
			if (i != n)
				cout << ",";
		}
		cout << endl;
	}
}

int main() {

	setlocale(LC_ALL, ".1251");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string K = "001101110";
	linear_complexity_profile(K);

	return 0; 
}