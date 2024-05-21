#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include "klasy.h"

using namespace std;

void menu()
{
	{
		Admin admin;
		string login, haslo;

		size_t rozmiar = 0;
		nr_rows(rozmiar);
		string *nr = new string[rozmiar];
		string *passwd = new string[rozmiar];

		read_from_list_of_passwd(nr, passwd, rozmiar);

		cout << "Podaj swoj login: ";
		cin >> login;
		cout << "Podaj swoj haslo: ";
		cin >> haslo;

		if (admin.get_login() == login && admin.get_haslo() == haslo)
		{
			menu_admin();
		}

		for (int i = 0; i < rozmiar; i++)
		{
			if (nr[i] == login && passwd[i] == haslo)
			{
				menu_student();
			}
		}
		delete[] nr, passwd;
	}
}