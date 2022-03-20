#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

void encrypt() {
	int n, m;
	cout << "Введите размеры блока шифрования (длина и высота через пробел): ";
	cin >> n >> m;
	cout << "Введите ключ шифрования: ";
	string key;
	key.resize(n);
	cin >> key;
	cout << "Введите текст: ";
	string input[2];
	cin.ignore();
	getline(cin, input[1]);
	if (input[1].length() % (m * n) != 0) input[1].resize((input[1].length() / (m * n) + 1) * m * n, ' ');
	input[0].resize(input[1].length());
	for (int i = 0; i < input[1].length();) {
		for (int j = 0; j < n; j++) {
			input[0][i] = key[j];
			i++;
			if (i == input[1].length()) break;
		}
	}
	cout << input[0] << endl;
	cout << input[1] << endl;
	cout << "Зашифрованный текст: ";
	for (int block_counter = 0; block_counter < input[1].length() / (m * n); block_counter++) {
		for (int j = 1; j <= n; j++) {
			for (int i = block_counter * n * m; i < (block_counter + 1) * n * m; i++) {

				if (input[0][i] - '0' == j) cout << input[1][i];
			}
		}
	}
}

void decrypt() {
	int n, m;
	cout << "Введите размеры блока шифрования (длина и высота через пробел): ";
	cin >> n >> m;
	cout << "Введите ключ шифрования: ";
	string key;
	key.resize(n);
	cin >> key;
	cout << "Введите текст: ";
	string input[2];
	cin.ignore();
	getline(cin, input[1]);
	if (input[1].length() % (m * n) != 0) input[1].resize((input[1].length() / (m * n) + 1) * m * n, ' ');
	input[0].resize(input[1].length(), ' ');
	int counter = 1;
	for (int i = 0; i < input[1].length();) {
		for (int j = i; j < i + m; j++) {
			input[0][j] = counter + '0';
		}
		i += m;
		counter++;
		if (counter > n) counter = 1;
	}
	cout << input[0] << endl;
	cout << input[1] << endl;
	cout << "Расшифрованный текст: ";
	int blocks = input[1].length() / m;
	for (int count = 0; count < blocks; count++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < input[1].length(); j++) {
				if (input[0][j] == key[i]) {
					cout << input[1][j];
					input[0].erase(j, 1);
					input[1].erase(j, 1);
					break;
				}
			}
		}
	}
};

void main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int option;
	bool stop = false;
	do {
		cout << endl << "Выберите режим работы: " << endl << "[1] Шифровка текста" << endl << "[2] Дешифровка текста" << endl << "[3] Выход" << endl << "Выбор: ";
		cin >> option;
		switch (option) {
		case 1: {encrypt(); break; }
		case 2: {decrypt(); break; }
		case 3: stop = true;
		}
	} while (stop != true);
}