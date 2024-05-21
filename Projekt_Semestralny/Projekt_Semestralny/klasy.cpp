#include "klasy.h"
#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <vector>

using namespace std;

//===================================| METODY KLAS |===================================

//metody klasy Student:

void Student::rejestruj()
{
	Student *student;
	size_t size = 1;

	create_user(student);

	gen_nr_albumu(*student);
	insert_imie_nazwisko(*student);
	gen_passwd(*student);

	system("cls");

	save_to_list_of_students(student, size);
	save_to_list_of_passwd(student, size);

	print(student);
	delete_user(student);
}

void Student::set_nr_albumu(size_t liczba) { nr_albumu = liczba; }
size_t Student::get_nr_albumu() { return nr_albumu; }

void Student::set_imie() { cin >> imie; }
string Student::get_imie() { return imie; }

void Student::set_nazwisko() { cin >> nazwisko; }
string Student::get_nazwisko() { return nazwisko; }

void Student::set_haslo(string passwd) { haslo = passwd; }
string Student::get_haslo() { return haslo; }

//metody klasy Dziennik:
Dziennik::Dziennik() : student{ new Student }
{
	gen_nr_albumu(*student);
	gen_passwd(*student);
	insert_imie_nazwisko(*student);
	system("cls");

	przedmiot.push_back(new Przedmiot);

}
Dziennik::Dziennik(const Dziennik& copy)
{	
	student = new Student;


	*student = *copy.student;
	
	for(int i=0;i<ilosc_przedmiotow;i++)
	{
		*przedmiot[i] = *copy.przedmiot[i];
	}
}  
Dziennik::~Dziennik() {
	delete student;
	
	delete &przedmiot;

	ilosc_przedmiotow = 0;
}

void Dziennik::pokaz() const {
	string obecnosc;
	print(student);
	if (ilosc_przedmiotow > 0)
		cout << endl << "Przedmioty:" << endl;
	for (size_t i = 0; i < ilosc_przedmiotow; ++i)
	{
		if (przedmiot[i]->obecnosc == false)obecnosc = "nb";
		else string obecnosc = "ob";
		cout << *przedmiot[i] << " Obecnosc: " << obecnosc << endl;
	}
		
}

//metody klasy Nauczyciel:
void Nauczyciel::rejestruj()
{
	Nauczyciel *nauczyciel;

	create_user(nauczyciel);

	insert_imie_nazwisko(*nauczyciel);
	gen_passwd(*nauczyciel);

	system("cls");

	print(nauczyciel);
	delete_user(nauczyciel);
}

string Nauczyciel::get_login() { return login; }

void Nauczyciel::set_imie() { cin >> imie; }
string Nauczyciel::get_imie() { return imie; }

void Nauczyciel::set_nazwisko() { cin >> nazwisko; }
string Nauczyciel::get_nazwisko() { return nazwisko; }

void Nauczyciel::set_przedmiot() { cin >> przedmiot; }
string Nauczyciel::get_przedmiot() { return przedmiot; }

void Nauczyciel::set_haslo(string passwd) { haslo = passwd; }
string Nauczyciel::get_haslo() { return haslo; }

//metody klasy Admin:
string Admin::get_login() const { return login; }
string Admin::get_haslo() const { return haslo; }

//========================================| FUNKCJE |=========================================

//przecia¿anie operatorów:
ostream& operator<<(ostream& stream, Dziennik::Przedmiot& other)
{
	stream << "Nazwa przedmiotu: " << other.nazwa_przedmiotu << " Ocena:" << other.ocena;
	return stream;
}
/*Dziennik& Dziennik::operator=(const Dziennik& prawy)
{
	if (&prawy != this)
	{	

		ilosc_przedmiotow = prawy.ilosc_przedmiotow;

		
	}
	return*this;
}*/

//generator liczb:
size_t generator_liczb(size_t begin, size_t end) {
	random_device seed;     // ziarno poczatkowe
	mt19937 engine(seed()); // generator
	uniform_int_distribution<size_t> uniformDist(begin, end);
	return uniformDist(engine);
}

//zliczanie wierszy w pliku:
void nr_rows(size_t& rozmiar)
{
	fstream baza_studentow;
	size_t ile = 0;
	string linia="";

	baza_studentow.open("baza_passwd.txt", ios::in);

	if (!baza_studentow) {

	}
	else {

		while (!baza_studentow.eof())
		{
			getline(baza_studentow, linia);
			ile++;
		}

		rozmiar = ile;

		baza_studentow.close();
	}
}

//generowanie has³a:
template<class t>void gen_passwd(t& user)
{
	size_t number;
	string char_set = "qQ!wW@eE#rR$tT%yY&uUiI1oO2pP3aA4sS5dD6fF7gG8hH9jJ0kKlLzZxXcCvVbBnNmM";
	string gen_passwd = "";
	for (size_t j = 0; j < 8; j++)
	{
		number = generator_liczb(0, 68);
		gen_passwd += char_set[number];
	}

	user.set_haslo(gen_passwd);

}
template<class t>void gen_passwd(t*& user, const size_t rozmiar)
{
	size_t number;
	string char_set = "qQ!wW@eE#rR$tT%yY&uUiI1oO2pP3aA4sS5dD6fF7gG8hH9jJ0kKlLzZxXcCvVbBnNmM";
	string gen_passwd;

	for (size_t i = 0; i < rozmiar; i++)
	{
		gen_passwd = "";

		for (size_t j = 0; j < 8; j++)
		{
			number = generator_liczb(0, 68);
			gen_passwd += char_set[number];
		}

		user[i].set_haslo(gen_passwd);
	}

}

//rezerwowanie miejsca w pamiêci:
template<class t>void create_user(t*& user)
{
	user = new t;
}
template<class t>void create_user(t*& user, const size_t rozmiar) {
	user = new t[rozmiar];
}

//zwalnianie miejsca w pamiêci:
template<class t>void delete_user(t*& user)
{
	delete user;
	user = nullptr;
}
template<class t>void delete_user(t*& user, const size_t rozmiar) {
	delete[] user;
	user = nullptr;
}

//===================================| FUNKCJE NAUCZYCIELA |==================================

void insert_imie_nazwisko(Nauczyciel& nauczyciel)
{
	
	cout << "Wprowadz imie" << " nauczyciela: ";
	nauczyciel.set_imie();
	cout << "Wprowadz nazwisko" << " nauczyciela: ";
	nauczyciel.set_nazwisko();
	cout << "Wprowadz przedmiot" << " nauczyciela: ";
	nauczyciel.set_przedmiot();
	system("cls");
	

}
void print(Nauczyciel* nauczyciel)
{
	cout << "Pomyslnie stworzono nauczyciela i wygenerowano dla niego hasla: \n";
	
	cout << nauczyciel->get_imie() << " " << nauczyciel->get_nazwisko() << " " << nauczyciel->get_przedmiot() << " " << nauczyciel->get_haslo() << endl;
	
}

//====================================| FUNKCJE STUDENTA |====================================

//generowanie nr_albumu:
void gen_nr_albumu(Student& student)
{
	size_t a = generator_liczb(10000, 20000);
	student.set_nr_albumu(a);
}
void gen_nr_albumu(Student*& student, const size_t rozmiar)
{
	for (int i = 0; i < rozmiar; i++)
	{
		size_t a = generator_liczb(10000, 20000);
		student[i].set_nr_albumu(a);
	}
}

//wpisywanie imienia i nazwiska dla studenta:
void insert_imie_nazwisko(Student& student)
{
	string imie;
	cout << "Wprowadz imie: ";
	student.set_imie();
	cout << "Wprowadz nazwisko: ";
	student.set_nazwisko();
}
void insert_imie_nazwisko(Student*& student, const size_t rozmiar)
{
	for (int i = 0; i < rozmiar; i++)
	{
		cout << "Wprowadz imie " << " studenta: ";
		student[i].set_imie();
		cout << "Wprowadz nazwisko " << " studenta: ";
		student[i].set_nazwisko();
		system("cls");
	}

}

//wypisywanie danych:
void print(Student* student)
{
	cout << "Pomyslnie stworzono studenta i wygenerowano dla niego haslo: \n"  << student->get_nr_albumu() << " " << student->get_imie() << " " << student->get_nazwisko() << " " << student->get_haslo() << endl;
}
void print(Student* student, const size_t rozmiar)
{
	cout << "Pomyslnie stworzono studentow i wygenerowano dla nich hasla: \n";
	for (int i = 0; i < rozmiar; i++)
	{
		cout << student[i].get_nr_albumu() << " " << student[i].get_imie() << " " << student[i].get_nazwisko() << " " << student[i].get_haslo() << endl;
	}
}

//zapisyawnie danych do pliku:
void save_to_list_of_students(Student* student, size_t const rozmiar)
{
	fstream baza_studentow;
	baza_studentow.open("baza_studentow.txt", ios::out | ios::app);

	if (!baza_studentow) {}
	else {

		for (int i = 0; i < rozmiar; i++)
		{
			baza_studentow << student[i].get_nr_albumu() << " " << student[i].get_imie() << " " << student[i].get_nazwisko() << "\n";
		}

		baza_studentow.close();
	}
}
void save_to_list_of_passwd(Student* student, size_t const rozmiar)
{
	fstream baza_passwd;
	baza_passwd.open("baza_passwd.txt", ios::out | ios::app);

	if (!baza_passwd) {}
	else {

		for (int i = 0; i < rozmiar; i++)
		{
			baza_passwd << student[i].get_nr_albumu() << " " << student[i].get_haslo() << "\n";
		}

		baza_passwd.close();
	}
}

//odczytywanie danych z pliku:
void read_from_list_of_students(Student* student)
{
	fstream baza_studentow;
	baza_studentow.open("baza_studentow.txt", ios::in);

	if (!baza_studentow) {

	}
	else {
		int nr;
		string imie, nazwisko;

		while (true) {
			baza_studentow >> nr >> imie >> nazwisko;
			if (baza_studentow.eof())
				break;
			cout << nr << " " << imie << " " << nazwisko << endl;
		}
	}
	baza_studentow.close();
}
void read_from_list_of_passwd(string*& nr, string*& passwd, size_t const rozmiar) {
	fstream baza_passwd;
	baza_passwd.open("baza_passwd.txt", ios::in);

	if (!baza_passwd) {

	}
	else {

		for (int i = 0; i < rozmiar; i++)
		{
			baza_passwd >> nr[i] >> passwd[i];
			if (baza_passwd.eof())
				break;
		}
	}
	baza_passwd.close();
}

//inicjalizacja:
void new_student()
{
	Student *student;
	size_t size = 1;

	create_user(student);

	gen_nr_albumu(*student);
	insert_imie_nazwisko(*student);
	gen_passwd(*student);

	system("cls");

	print(student);

	save_to_list_of_students(student, size);
	save_to_list_of_passwd(student, size);

	delete_user(student);
}
void new_students()
{
	Student *student;

	size_t size;
	cout << "Wprowadz ilu studentow stworzyc" << endl;
	cin >> size;

	system("cls");

	create_user(student, size);

	gen_nr_albumu(student, size);
	insert_imie_nazwisko(student, size);
	gen_passwd(student, size);

	system("cls");

	print(student, size);

	save_to_list_of_students(student, size);
	save_to_list_of_passwd(student, size);

	delete_user(student, size);
}
void kopiowanie()
{
	Dziennik D;

	
	D.pokaz();

}
void polimorfizm()
{
	Student student;
	Nauczyciel nauczyciel;
	vector<Osoba*>wydzial;
	
	wydzial.push_back(&student);
	wydzial.push_back(&nauczyciel);
	
	for(int i=0;i<2;i++)
	{
		wydzial[i]->rejestruj();
		cout << "\nwiek: " << wydzial[i]->get_wiek() << endl;
		system("pause");
		system("cls");
	}
}

//========================================| MENU |=========================================
void menu_admin()
{
	bool exit = true;

	do
	{
		int x;
		system("cls");

		cout << "Pomyslnie zalogowano" << endl;
		cout << "Menu Wyboru\n1.Stworz jednego studenta\n2.Stworz kilku studentow\n3.Polimorfizm\n4.opertory: <<, =, []\n5.Wyloguj" << endl;

		cin >> x;
		switch (x)
		{
		case 1:
			system("cls");
			new_student();
			system("pause");
			break;
		case 2:
			system("cls");
			new_students();
			system("pause");
			break;
		case 3:
			system("cls");
			polimorfizm();
			system("pause");
			break;
		case 4:
			system("cls");
			kopiowanie();
			system("pause");
			break;
		case 5:
			system("cls");
			cout << "Pomyslnie wylogowano" << endl;
			exit = false;
			system("pause");
			break;
		}

	} while (exit != false);
}
void menu_student()
{

	bool exit = true;

	do
	{
		int x;
		system("cls");

		cout << "Pomyslnie zalogowano" << endl;
		cout << "Menu Wyboru\n1.Wyswietl oceny\n2.Wyswietl terminarz\n3.Wyloguj" << endl;

		cin >> x;
		switch (x)
		{
		case 1:
			system("cls");

			system("pause");
			break;
		case 2:
			system("cls");

			system("pause");
			break;
		case 3:
			system("cls");
			cout << "Pomyslnie wylogowano" << endl;
			exit = false;
			system("pause");
			break;
		}

	} while (exit != false);
}