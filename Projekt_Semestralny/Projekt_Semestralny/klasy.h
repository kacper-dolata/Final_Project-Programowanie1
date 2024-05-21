#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;
//====================================| FUNKCJE |===================================

//zliczanie wierszy w pliku:
void nr_rows(size_t& rozmiar);

//generator liczb:
size_t generator_liczb(size_t begin, size_t end);

//=====================================| KLASY |====================================
class Osoba
{
	size_t wiek;
public:
	Osoba():wiek{ generator_liczb(40,60) }{}
	virtual ~Osoba()
	{
		cout << "\ndestruktor Osoba" << endl;
	}

	virtual int get_wiek() { return wiek; }
	virtual void rejestruj() = 0;
};

class Student:public Osoba
{
	string imie;
	size_t nr_albumu;
	string nazwisko;
	string haslo;

public:

	virtual ~Student()
	{
		cout << "\ndestruktor Student" << endl;
	}
	virtual int get_wiek() { return round(Osoba::get_wiek() / 2); }
	virtual void rejestruj();

	void set_nr_albumu(size_t liczba);
	void set_imie();
	void set_nazwisko();
	void set_haslo(string passwd);

	size_t get_nr_albumu();
	string get_imie();
	string get_nazwisko();
	string get_haslo();
};

class Dziennik
{
	class Przedmiot
	{
		friend class Dziennik;
		string nazwa_przedmiotu{"niepodano"};
		size_t ocena{0};
		bool obecnosc{false};
		
	public:
		Przedmiot() = default;
		friend ostream& operator<<(ostream& stream, Dziennik::Przedmiot& other);
	};

	size_t ilosc_przedmiotow{ 1 };
	vector<Przedmiot*> przedmiot;
	Student *student{ nullptr };

public:
	Dziennik();
	Dziennik(const Dziennik& copy);
	~Dziennik();
	Dziennik& operator=(const Dziennik& dziennikprawy);
	Przedmiot* operator [](const size_t index)
	{
		return przedmiot[index];
	}
	friend ostream& operator<<(ostream& stream, Dziennik::Przedmiot& other);
	
	void pokaz() const;
};

class Nauczyciel:public Osoba
{
	string login;
	string haslo;
	string imie;
	string nazwisko;
	string przedmiot;
public:

	virtual ~Nauczyciel()
	{
		cout << "\ndestruktor Nauczyciel" << endl;
	}

	virtual int get_wiek() { return Osoba::get_wiek(); }
	virtual void rejestruj();

	void set_imie();
	void set_nazwisko();
	void set_przedmiot();
	void set_haslo(string passwd);

	string get_imie();
	string get_nazwisko();
	string get_przedmiot();
	string get_login();
	string get_haslo();
};

class Admin
{
	 const string login;
	 const string haslo;

public:
	Admin() : login{ "admin" }, haslo{ "admin" } {};

	string get_login() const;
	string get_haslo() const;

};

//================================| FUNKCJE UNIWERSALNE|============================

//generowanie has³a:
template<class t>void gen_passwd(t& user);
template<class t>void gen_passwd(t*& user, const size_t rozmiar);

//rezerwowanie miejsca w pamiêci:
template<class t>void create_user(t*& user);
template<class t>void create_user(t*& user, const size_t rozmiar);

//zwalnianie miejsca w pamiêci:
template<class t>void delete_user(t*& user);
template<class t>void delete_user(t*& user, const size_t rozmiar);

//================================| FUNKCJE NAUCZYCIELA |===========================
void insert_imie_nazwisko(Nauczyciel& nauczyciel);
void print(Nauczyciel* nauczyciel);

//================================| FUNKCJE STUDENTA |==============================

//generowanie nr_albumu:
void gen_nr_albumu(Student& student);
void gen_nr_albumu(Student*& student, const size_t rozmiar);

//wpisywanie imienia i nazwiska dla studenta:
void insert_imie_nazwisko(Student& student);
void insert_imie_nazwisko(Student*& student, const size_t rozmiar);

//wypisywanie danych:
void print(Student* student);
void print(Student* student, const size_t rozmiar);

//zapisyawnie danych do pliku:
void save_to_list_of_students(Student* student, size_t const rozmiar);
void save_to_list_of_passwd(Student* student, size_t const rozmiar);

//odczytywanie danych z pliku:
void read_from_list_of_students(Student* student);
void read_from_list_of_passwd(string*& nr, string*& passwd, size_t const rozmiar);

//========================================| MENU |=========================================
void menu_admin();
void menu_student();

void menu();