#pragma once
#include "Date.h"
#include <vector>
#include <list>
#include <string>
#include <functional>

using namespace std;

enum class book_status //Статус книги
{
	is_available, //книга доступна
	is_issued // книга выдана		
};

ostream& operator<< (ostream& out, const book_status& status);
istream& operator>> (istream& in, book_status& status);

class Book //Книга
{
private:
	string author_of_book; // автор книги
	string name_of_book; // название
	int year_of_publication; // год издательства
	string publishing_house; // издательство
public:
	string get_author_of_book() const;
	string get_name_of_book() const;
	int get_year_of_publication() const;
	string get_publishing_house() const;

	void set_author_of_book(const string& author);
	void set_name_of_book(const string& name);
	void set_year_of_publication(const int year);
	void set_publishing_house(const string& house);

	void input_author_of_book();
	void input_name_of_book();
	void input_year_of_publication();
	void input_publishing_house();	

	friend bool operator== (const Book& book1, const Book& book2);
	friend bool operator!= (const Book& book1, const Book& book2);
	friend ostream& operator<< (ostream& out, const Book& book);
	friend istream& operator>> (istream& in, Book& book);
};

class BookInfo //Информационная запись о книге в библиотеке
{
private:
	Book book; // книга
	book_status status; // текущий статус книги
public:
	BookInfo(const Book& book);
	BookInfo();

	Book& get_book();
	book_status get_status() const;

	void set_book(const Book& book);
	void set_status(const bool status);

	void input_field_by_num(int n);
	void print_field_by_num(int n);
	static function<void(BookInfo&)> get_print_func(bool status); //форматированная печать записи
	static function<bool(BookInfo&, BookInfo&)> get_compare_func_by_num(int n); //возвращает компаратор по номеру поля
	static void print_name_sort_field(int n); //печатает название поля для сортировки по его номеру
	static int get_num_selected_field(const string& name, bool canBack = false); //функция выбора поля записи для какого-либо действия

	void input_status();
	friend ostream& operator<< (ostream& out, const BookInfo& book);
	friend istream& operator>> (istream& in, BookInfo& book);
};

class IssuedBook //Информационная запись о книге, взятой читателем на руки с датой выдачи
{
private:
	Date issue_date; // дата выдачи книги
	Book book; // книга	
public:
	Book& get_book();
	Date get_issue_date() const;

	void set_book(const Book& book);
	void set_issue_date(const Date& date);

	IssuedBook();
	IssuedBook(const Book& book, const Date& issue_date);

	friend ostream& operator<< (ostream& out, const IssuedBook& issued_book);
	friend istream& operator>> (istream& in, IssuedBook& issued_book);
};
