#pragma once
#include "Book.h"
#include "Date.h"
#include <string>
#include <list>

using namespace std;

class Reader //Читатель
{
private:
	int number_of_library_card; // номер читательского билета
	string surname; // фамилия абонента
public:
	int get_number_of_library_card() const;
	string get_surname() const;

	void set_number_of_library_card(const int number);
	void set_surname(const string& surname);

	void input_number_of_library_card();
	void input_surname();

	friend ostream& operator<< (ostream& out, const Reader& reader);
	friend istream& operator>> (istream& in, Reader& reader);
};

class ReaderInfo //Информационная запись о читателе в библиотеке с указанием всех выданных ему книг
{
private:
	Reader reader; // читатель
	list<IssuedBook> books_on_hand; // список книг, которые находятся у читателя
public:
	Reader& get_reader();
	void set_reader(const Reader& reader);

	void take_book(const IssuedBook& issued_book); //взять книгу
	bool has_chosen_book(Book& book, Date& issue_date); //проверить наличие выбранной книги у читателя
	void show_books_on_hand(); //отобразить пользователю все книги, которые он брал и не вернул
	int get_count_books_on_hand(); //получить количество книг на руках у читателя
	void return_book(Book& book); //вернуть книгу в библиотеку
	bool has_books_on_hand(); //узнать, есть ли книги у читателя на руках

	friend ostream& operator<< (ostream& out, const ReaderInfo& reader_info);
	friend istream& operator>> (istream& in, ReaderInfo& reader_info);
};

